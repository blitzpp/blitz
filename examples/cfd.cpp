/*
 * This is a small 4th-order Computational Fluid Dynamics solver.  It
 * illustrates multicomponent arrays (i.e. vector fields) and stencil
 * objects.  It is implemented in "C++Tran" style for simplicity.
 *
 * Incompressible flow is assumed.
 *
 * The simulation is of water in a closed cube.  The water is initially
 * quiescent.  At a single layer near the bottom of the cube, a forcing
 * function simulates the effect of a (highly idealized) propeller.
 *
 * Thanks to Stephen Smith (ACL/LANL) for help with the math.
 */

/*
 * This is a "work in progress".  Things I am unhapppy about:
 *   - arrays, geometry, and boundary conditions are separate objects.
 *     This results in a certain amount of kludginess.  For example,
 *     the stencil operators take geometry as a 2nd parameter.
 *     On the plus side, one geometry object is shared among many
 *     arrays.
 *   - The new stencil objects are nice, but declaring a new stencil
 *     object for every single equation seems like overkill.  It would
 *     be nice if stencil operators could be "expression templatized"
 *     so that these equations could be moved to the appropriate place
 *     in the code.  This probably wouldn't be too much work.
 *   - Stencil objects can't take scalar arguments, so all the scalars
 *     have to be globals.  Big ugh.  There is a fix for this,
 *     but it hasn't been implemented yet.
 *   - There are serious bugs, this simulation doesn't work very well.
 */

#define NO_STIRRING
#undef NO_GRAVITY

#include <blitz/array-old.h>     
#include <blitz/array/cgsolve.h>
#ifdef BZ_HAVE_STD
	#include <fstream>
#else
	#include <fstream.h>
#endif

BZ_USING_NAMESPACE(blitz)

/*
 * The current implementation of stencil objects forces these variables
 * to be placed in global scope.  Ugh.  This restriction will be removed
 * eventually.
 */
double rho;                        // Density of fluid
double recip_rho;                  // 1/rho
double eta;                        // Kinematic viscosity
double time_now;                   // Elapsed seconds
double delta_t;                    // Time step
double volume;                     // Volume of a cell
double airPressure;                // Air pressure (Pa)
double spatialStep;                // Grid element size
double gravity;                    // Acceleration due to gravity
double gravityPressureGradient;    // Pressure gradient due to gravity

/*
 * The "geometry" object specifies how an array is mapped into real-world
 * space.  In this case, "UniformCubicGeometry" is used, which means that
 * the real-world grid is orthogonal, regularly spaced, with the same spatial
 * step in each dimension.
 */

UniformCubicGeometry<3> geom;      // Geometry

/*
 * Some typedefs to make life easier.
 */

typedef TinyVector<double,3> vector3d;
typedef Array<vector3d,3> vectorField;
typedef Array<double,3>   scalarField;

/*
 * Function prototypes
 */

void record(vectorField& V);
void snapshot(scalarField&);
void snapshot(vectorField&);


/***********************************************************************
 *
 * Stencil objects involve these arrays:
 *
 * V       Velocity (vector field)
 * nextV   Velocity field at next time step (vector field)
 * advect  Advection (vector field)
 * P       Pressure (scalar field)
 * force   Force (vector field)
 * rhs     Right-hand side of the pressure equation (scalar field)
 *
 * These stencil operators are used:
 *
 * grad3DVec4        4th-order gradient of a vector field (Jacobian matrix)
 * Laplacian3DVec4   4th-order Laplacian of a vector field
 * grad3D4           4th-order gradient of a scalar field
 * div3DVec4         4th-order divergence of a vector field
 *
 ***********************************************************************/


/***********          Advection Calculation Stencil         ************/

BZ_DECLARE_STENCIL2(calc_advect, advect, V)

    advect = product(grad3DVec4(V,geom), *V);

BZ_END_STENCIL


/***********          Timestep the velocity field           ************
 * This is a 63-point stencil.  For example, Laplacian3DVec4 turns into
 * a 45-point stencil: each 2nd derivative is a 5-point stencil, and
 * there are 9 of these derivatives to take the Laplacian of a 3D vector
 * field.
 */

BZ_DECLARE_STENCIL5(timestep, V, nextV, P, advect, force)

    nextV = *V + delta_t * ( recip_rho * (
      eta * Laplacian3DVec4(V,geom) - grad3D4(P, geom) + *force) - *advect);

BZ_END_STENCIL

/***********     Calculate the RHS of the pressure eqn      ************/


BZ_DECLARE_STENCIL2(calc_P_rhs, rhs, advect)

    rhs = - rho * div3DVec4(advect, geom);

BZ_END_STENCIL

/***********    Pressure equation update for the solver     ************/

BZ_DECLARE_STENCIL2(P_solver_update, result, P)

    result += Laplacian3D4(P,geom);

BZ_END_STENCIL


/*
 * Allocate arrays and set their initial state
 */
void setup(const int N, vectorField& V, vectorField& nextV, scalarField& P,
    scalarField& P_rhs, vectorField& advect, vectorField& force)
{
    // A 1m x 1m x 1m domain
    spatialStep = 1.0 / (N - 1);
    geom = UniformCubicGeometry<3>(spatialStep);

    // Allocate arrays
    allocateArrays(shape(N,N,N), advect, V, nextV, force);  // vector fields
    allocateArrays(shape(N,N,N), P, P_rhs);                 // scalar fields

    // Since incompressibility is assumed, pressure only shows up as
    // derivative terms in the equations.  We choose airPressure = 0
    // as an arbitrary datum.

    airPressure = 0;             // Pa
    rho = 1000;                  // density of fluid, kg/m^3
    recip_rho = 1.0 / rho;       // inverse of density
    eta = 1.0e-6;                // kinematic viscosity of fluid, m^2/s
    gravity = 9.81;              // m/s^2
    delta_t = 0.001;             // initial time step, in seconds
    volume = pow3(spatialStep);  // cubic volume associated with grid point

    // Kludge: Set eta high, so that the flow will spread faster.
    // This means the cube is filled with molasses, rather than water.
    eta *= 1000;
   
    // Initial conditions: quiescent
    V = 0.0; 
    P_rhs = 0.0;
    advect = 0.0;
    nextV = 0.0;

    // Initial pressure condition: gravity causes a linear increase
    // in pressure with depth.  Note that tensor::k means the index
    // associated with the z axis (they are labelled i, j, k).
#ifdef NO_GRAVITY
    gravityPressureGradient = 0.0;
    P = 0.0;
#else
    gravityPressureGradient = spatialStep * gravity * rho;

#ifdef BZ_NAMESPACES
    P = airPressure + tensor::k * gravityPressureGradient;
#else
    P = airPressure + k * gravityPressureGradient;
#endif

#endif

    // Set up the forcing function: gravity plus a stirring force
    // at the bottom
    double gravity_z = gravity * rho;

    const int x = 0, y = 1, z = 2;
    force[x] = 0.0;
    force[y] = 0.0;
#ifdef NO_GRAVITY
    force[z] = 0.0;
#else
    force[z] = gravity_z;    
#endif

#ifndef NO_STIRRING
    // Centre of the stirring
    int centrex = int(2 * N / 3.0);
    int centrey = int(2 * N / 3.0);
    int centrez = int(4 * N / 5.0);

    const double stirRadius = 1.0 / 3.0;

    vector3d zaxis(0,0,1);

    // Loop through the 2D slice where the stirring occurs

    for (int i=force.lbound(firstDim); i <= force.ubound(firstDim); ++i)
    {
      for (int j=force.lbound(secondDim); j <= force.ubound(secondDim); ++j)
      {
         // Vector from the centre of the stirring to the current
         // coordinate

         vector3d r((i-centrex) * spatialStep, (j-centrey) * spatialStep, 0.0);

         if (norm(r) < stirRadius)
         {
             // The cross product of the z-axis and the vector3d to this
             // coordinate yields the direction of the force.  Multiply
             // by gravity to get a reasonable magnitude (max force =
             // 5 * gravity)
             force(i,j,centrez) += cross(zaxis, r) 
                 * (5 * gravity_z / stirRadius);
         }
      }
    }
#endif // NO_STIRRING
}

// Calculate a simple check on a vector field
void record(vectorField& V)
{
    // Calculate the magnitude of a field
    const int x=0, y=1, z=2;
    double magx = sum(pow2(V[x])) / V.numElements();
    double magy = sum(pow2(V[y])) / V.numElements();
    double magz = sum(pow2(V[z])) / V.numElements();

    cout << "norm = [" << magx
        << " " << magy << " " << magz << " ]" << endl;
}

// Boundary conditions for the pressure field

class PressureBCs {
public:
    PressureBCs(double gravityPressureGradient)
      : gravityPressureGradient_(gravityPressureGradient)
    {  }
        
    void applyBCs(scalarField& P) const
    {
        // Apply the Neumann boundary condition that grad(P) dot surface = 0
        int xN = P.ubound(firstDim);
        int yN = P.ubound(secondDim);
        int zN = P.ubound(thirdDim);

        Range all = Range::all();

        // lower x
        P(0,all,all) = P(2,all,all);
        P(1,all,all) = P(2,all,all);

        // upper x
        P(xN,all,all) = P(xN-2,all,all);
        P(xN-1,all,all) = P(xN-2,all,all);

        // lower y
        P(all,0,all) = P(all,2,all);
        P(all,1,all) = P(all,2,all);

        // upper y
        P(all,yN,all) = P(all,yN-2,all);
        P(all,yN-1,all) = P(all,yN-2,all);

        // lower z
        P(all,all,0) = P(all,all,2) - 2*gravityPressureGradient_;
        P(all,all,1) = P(all,all,2) - gravityPressureGradient_;

        // upper z
        P(all,all,zN) = P(all,all,zN-2) + 2*gravityPressureGradient_;
        P(all,all,zN-1) = P(all,all,zN-2) + gravityPressureGradient_;
    }

private:
    double gravityPressureGradient_;
};

/*
 * One iteration: calculate advection, solve the pressure equation,
 * then time step.
 */

void iterate(vectorField& V, vectorField& nextV, scalarField& P,
    scalarField& P_rhs, vectorField& advect, vectorField& force)
{
    // Calculate advection term
    applyStencil(calc_advect(), advect, V);

    // Solve to find the pressure
    applyStencil(calc_P_rhs(), P_rhs, advect);
    conjugateGradientSolver(P_solver_update(), P, P_rhs, 1e-8, 
        PressureBCs(gravityPressureGradient));

    // Time step
    applyStencil(timestep(), V, nextV, P, advect, force);
    cycleArrays(V, nextV);

    // Record some information about this time step
    cout << "Velocity field: "; record(V);
}

/*
 * Adjust the time step according to the CFL stability criterion
 */
void adjustTimeStep(vectorField& V)
{
    // Find maximum velocity magnitude
    double maxV = 0.0;

    // NEEDS_WORK: Blitz should provide a norm(vectorField) function.
    // This is ugly.

    for (int i=V.lbound(0); i <= V.ubound(0); ++i)
      for (int j=V.lbound(1); j <= V.ubound(1); ++j)
        for (int k=V.lbound(2); k <= V.ubound(2); ++k)
        {
            double normV = norm(V(i,j,k));
            if (normV > maxV)
                maxV = normV;
        }

    cout << "Maximum velocity is " << maxV << " m/s" << endl;

    maxV += 1e-10;   // Avoid divide-by-zero

    // Steve K: need to have spatialStep^2 / diffusion constant
    // diffusion constant = eta * recip_rho

    delta_t = 0.3 * spatialStep / maxV;
    const double maxTimeStep = 0.01;

    if (delta_t > maxTimeStep)
        delta_t = maxTimeStep;

    cout << "Set time step to " << delta_t << " s" << endl;
}

/*
 *  Main program loop
 */

int main()
{
    vectorField V, nextV;        // Velocity fields
    scalarField P, P_rhs;        // Pressure fields
    vectorField advect;          // Advection field
    vectorField force;           // Forcing function

    const int N = 50;            // Arrays are NxNxN

    setup(N, V, nextV, P, P_rhs, advect, force);

    const int nIters = 999;

    // Stirring motion will stop at this time
    const double forceTurnOff = 25000.0;  // seconds

    for (int i=0; i < nIters; ++i)
    {
        cout << "Iteration " << i << " Time = " << time_now << " s" << endl;

        iterate(V, nextV, P, P_rhs, advect, force);

        // Update the current time, turn off the force when we pass
        // forceTurnOff

        double oldtime_now = time_now;
        time_now += delta_t;

        if ((time_now > forceTurnOff) && (oldtime_now <= forceTurnOff))
            force = 0.0;

        // Dump some state
        snapshot(V);
        snapshot(P);

        // Adjust the time step for the next iteration
        adjustTimeStep(V);
    }

    return 0;
}

void snapshot(scalarField& P)
{
    static int snapshotNum = 0;

    ++snapshotNum;
    char filename[128];
    sprintf(filename, "pressure%03d.m", snapshotNum);

    ofstream ofs(filename);
    int N = P.length(firstDim);

    int k = N/2;

    ofs << "P" << snapshotNum << " = [ ";
    for (int i=0; i < N; ++i)
    {
        for (int j=0; j < N; ++j)
        {
            float value = P(k,j,N-i-1);
            ofs << value << " ";
        }
        if (i < N-1)
            ofs << ";" << endl;
    }
    ofs << "];" << endl;
}

void snapshot(vectorField& P)
{
    static int snapshotNum = 0;

    ++snapshotNum;
    char filename[128];
    sprintf(filename, "velocity%03d.m", snapshotNum);

    ofstream ofs(filename);
    int N = P.length(firstDim);

    int k = N/2;

    ofs << "P" << snapshotNum << " = [ ";
    for (int i=0; i < N; ++i)
    {
        for (int j=0; j < N; ++j)
        {
            float value = norm(P(k,j,N-i-1));
            ofs << value << " ";
        }
        if (i < N-1)
            ofs << ";" << endl;
    }
    ofs << "];" << endl;
}

