// 'explicit' keyword
// BZ_EXPLICIT

class vector {
  public:
    explicit vector(double)
    { }
};

int main()
{
    double c = 5.0;
    vector x(c);
    return 0;
}

