#ifndef Query_h
#define Query_h

class Query
{
private:       // Private Attributes
   // TODO

public:        // Public Methods
   Query( void );
   Query( const Query& aorQuery );
   ~Query( void );

   Query& operator=( const Query& aorQuery );
};

#endif
