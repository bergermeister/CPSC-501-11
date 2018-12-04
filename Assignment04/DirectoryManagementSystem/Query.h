#ifndef Query_h
#define Query_h

#include <string>
class Query
{
private:       // Private Attributes
   char        vcSelection;  /**< Query Selection */
   std::string voSearch;     /**< Search Term */

public:        // Public Methods
   Query( void );
   Query(char ch, std::string SearchingTerm);
   Query( const Query& aorQuery );
   ~Query( void );

   Query& operator=( const Query& aorQuery );

   const char         MSelection( void ) const;
   const std::string& MSearch( void ) const;
};

#endif
