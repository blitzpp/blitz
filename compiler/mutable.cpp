// 'mutable' keyword
// BZ_MUTABLE

class num {

public:
   num(int z)
   { 
       x_ = z; 
       numReads_ = 0;
   }

   void set(int z)
   { x_ = z; }

   int get() const
   { 
       ++numReads_;
       return x_;
   }

private:
   int x_;
   mutable int numReads_;
};

int main()
{
   num q(4);
   q.set(5);
   int k = q.get();
   q.get();
   return 0;
}

