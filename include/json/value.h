#ifndef CPPTL_JSON_H_INCLUDED
# define CPPTL_JSON_H_INCLUDED

# include "forwards.h"
# include <string>
# include <vector>

# ifndef JSON_USE_CPPTL_SMALLMAP
#  include <map>
# else
#  include <cpptl/smallmap.h>
# endif
# ifdef JSON_USE_CPPTL
#  include <cpptl/forwards.h>
# endif

namespace Json {

   /** \brief Type of the value held by a Value object.
    */
   enum ValueType
   {
      nullValue = 0, ///< 'null' value
      intValue,      ///< signed integer value
      uintValue,     ///< unsigned integer value
      realValue,     ///< double value
      stringValue,   ///< UTF-8 string value
      booleanValue,  ///< bool value
      arrayValue,    ///< array value (ordered list)
      objectValue    ///< object value (collection of name/value pairs).
   };

   enum CommentPlacement
   {
      commentBefore = 0,        ///< a comment placed on the line before a value
      commentAfterOnSameLine,   ///< a comment just after a value on the same line
      commentAfter,             ///< a comment on the line after a value (only make sense for root value)
      numberOfCommentPlacement
   };

# ifdef JSON_USE_CPPTL
   typedef CppTL::AnyEnumerator<const char *> EnumMemberNames;
   typedef CppTL::AnyEnumerator<const Value &> EnumValues;
# endif

   /** \brief Represents a <a HREF="http://www.json.org">JSON</a> value.
    *
    * This class is a discriminated union wrapper that can represents a:
    * - signed integer [range: Value::minInt - Value::maxInt]
    * - unsigned integer (range: 0 - Value::maxUInt)
    * - double
    * - UTF-8 string
    * - boolean
    * - 'null'
    * - an ordered list of Value
    * - collection of name/value pairs (javascript object)
    *
    * The type of the held value is represented by a #ValueType and 
    * can be obtained using type().
    *
    * values of an #objectValue or #arrayValue can be accessed using operator[]() methods. 
    * Non const methods will automatically create the a #nullValue element 
    * if it does not exist. 
    * The sequence of an #arrayValue will be automatically resize and initialized 
    * with #nullValue. resize() can be used to enlarge or truncate an #arrayValue.
    *
    * The get() methods can be used to obtanis default value in the case the required element
    * does not exist.
    *
    * It is possible to iterate over the list of a #objectValue values using 
    * the getMemberNames() method.
    */
   class JSON_API Value 
   {
      friend class ValueIteratorBase;
   public:
      typedef std::vector<std::string> Members;
      typedef int Int;
      typedef unsigned int UInt;
      typedef ValueIterator iterator;
      typedef ValueConstIterator const_iterator;

      static const Value null;
      static const Int minInt;
      static const Int maxInt;
      static const UInt maxUInt;

   private:
      class CZString 
      {
      public:
         enum DuplicationPolicy 
         {
            noDuplication = 0,
            duplicate,
            duplicateOnCopy
         };
         CZString( int index );
         CZString( const char *cstr, DuplicationPolicy allocate );
         CZString( const CZString &other );
         ~CZString();
         CZString &operator =( const CZString &other );
         bool operator<( const CZString &other ) const;
         bool operator==( const CZString &other ) const;
         int index() const;
         const char *c_str() const;
      private:
         void swap( CZString &other );
         const char *cstr_;
         int index_;
      };

   public:
# ifndef JSON_USE_CPPTL_SMALLMAP
      typedef std::map<CZString, Value> ObjectValues;
# else
      typedef CppTL::SmallMap<CZString, Value> ObjectValues;
# endif

   public:
      Value( ValueType type = nullValue );
      Value( Int value );
      Value( UInt value );
      Value( double value );
      Value( const char *value );
      Value( const std::string &value );
# ifdef JSON_USE_CPPTL
      Value( const CppTL::ConstString &value );
# endif
      Value( bool value );
      Value( const Value &other );
      ~Value();

      Value &operator=( const Value &other );
      void swap( Value &other );

      ValueType type() const;

      bool operator <( const Value &other ) const;
      bool operator <=( const Value &other ) const;
      bool operator >=( const Value &other ) const;
      bool operator >( const Value &other ) const;

      bool operator ==( const Value &other ) const;
      bool operator !=( const Value &other ) const;

      int compare( const Value &other );

      const char *asCString() const;
      std::string asString() const;
# ifdef JSON_USE_CPPTL
      CppTL::ConstString asConstString() const;
# endif
      Int asInt() const;
      UInt asUInt() const;
      double asDouble() const;
      bool asBool() const;

      bool isBool() const;
      bool isInt() const;
      bool isUInt() const;
      bool isIntegral() const;
      bool isDouble() const;
      bool isNumeric() const;
      bool isString() const;
      bool isArray() const;
      bool isObject() const;

      bool isConvertibleTo( ValueType other ) const;

      /// Number of values in array or object
      UInt size() const;

      /// Removes all object members and array elements.
      void clear();

      /// Resize the array to size elements. 
      /// New elements are initialized to null.
      /// May only be called on nullValue or arrayValue.
      void resize( UInt size );

      /// Access an array element (zero based index ).
      /// If the array contains less than index element, then null value are inserted
      /// in the array so that its size is index+1.
      Value &operator[]( UInt index );
      /// Access an array element (zero based index )
      const Value &operator[]( UInt index ) const;
      /// If the array contains at least index+1 elements, returns the element value, 
      /// otherwise returns defaultValue.
      Value get( UInt index, 
                 const Value &defaultValue ) const;
      /// Returns true if index < size().
      bool isValidIndex( UInt index ) const;
      /// Append value to array at the end.
      /// Equivalent to jsonvalue[jsonvalue.size()] = value;
      Value &append( const Value &value );

      // Access an object value by name, create a null member if it does not exist.
      Value &operator[]( const char *key );
      // Access an object value by name, returns null if there is no member with that name.
      const Value &operator[]( const char *key ) const;
      // Access an object value by name, create a null member if it does not exist.
      Value &operator[]( const std::string &key );
      // Access an object value by name, returns null if there is no member with that name.
      const Value &operator[]( const std::string &key ) const;
# ifdef JSON_USE_CPPTL
      // Access an object value by name, create a null member if it does not exist.
      Value &operator[]( const CppTL::ConstString &key );
      // Access an object value by name, returns null if there is no member with that name.
      const Value &operator[]( const CppTL::ConstString &key ) const;
# endif
      /// Returns the member named key if it exist, defaultValue otherwise.
      Value get( const char *key, 
                 const Value &defaultValue ) const;
      /// Returns the member named key if it exist, defaultValue otherwise.
      Value get( const std::string &key,
                 const Value &defaultValue ) const;
# ifdef JSON_USE_CPPTL
      /// Returns the member named key if it exist, defaultValue otherwise.
      Value get( const CppTL::ConstString &key,
                 const Value &defaultValue ) const;
# endif
      /// Returns true if the object has a member named key.
      bool isMember( const char *key ) const;
      /// Returns true if the object has a member named key.
      bool isMember( const std::string &key ) const;
# ifdef JSON_USE_CPPTL
      /// Returns true if the object has a member named key.
      bool isMember( const CppTL::ConstString &key ) const;
# endif

      // Returns a list of the member names.
      Members getMemberNames() const;

# ifdef JSON_USE_CPPTL
      EnumMemberNames enumMemberNames() const;
      EnumValues enumValues() const;
# endif

      void setComment( const char *comment,
                       CommentPlacement placement );
      void setComment( const std::string &comment,
                       CommentPlacement placement );
      bool hasComment( CommentPlacement placement ) const;
      std::string getComment( CommentPlacement placement ) const;

      std::string toStyledString() const;

      const_iterator begin() const;
      const_iterator end() const;

      iterator begin();
      iterator end();

   private:
      struct CommentInfo
      {
         CommentInfo();
         ~CommentInfo();

         void setComment( const char *text );

         char *comment_;
      };

      struct MemberNamesTransform
      {
         typedef const char *result_type;
         const char *operator()( const CZString &name ) const
         {
            return name.c_str();
         }
      };

      union ValueHolder
      {
         Int int_;
         UInt uint_;
         double real_;
         bool bool_;
         char *string_;
         ObjectValues *map_;
      } value_;
      ValueType type_ : 8;
      bool allocated_ : 1;
      CommentInfo *comments_;
   };


   /** \brief Experimental and untested: base class for Value iterators.
    *
    */
   class ValueIteratorBase
   {
   public:
      typedef unsigned int size_t;
      typedef int difference_type;
      typedef ValueIteratorBase SelfType;

      ValueIteratorBase();
      explicit ValueIteratorBase( const Value::ObjectValues::iterator &current );

      bool operator ==( const SelfType &other ) const
      {
         return isEqual( other );
      }

      bool operator !=( const SelfType &other ) const
      {
         return !isEqual( other );
      }

      difference_type operator -( const SelfType &other ) const
      {
         return computeDistance( other );
      }

      /// Returns either the index or the member name of the referenced value as a Value.
      Value key() const;

      /// Returns the index of the referenced Value. -1 if it is not an arrayValue.
      Value::UInt index() const;

      /// Returns the member name of the referenced Value. "" if it is not an objectValue.
      const char *memberName() const;

   protected:
      Value &deref() const;

      void increment();

      void decrement();

      difference_type computeDistance( const SelfType &other ) const;

      bool isEqual( const SelfType &other ) const;

      void copy( const SelfType &other );

   private:
      Value::ObjectValues::iterator current_;
   };

   /** \brief Experimental and untested: const iterator for object and array value.
    *
    */
   class ValueConstIterator : public ValueIteratorBase
   {
   public:
      typedef unsigned int size_t;
      typedef int difference_type;
      typedef const Value &reference;
      typedef const Value *pointer;
      typedef ValueConstIterator SelfType;

      ValueConstIterator();
      /*! \internal Use by Value to create an iterator.
       */
      explicit ValueConstIterator( const Value::ObjectValues::iterator &current );
      SelfType &operator =( const ValueIteratorBase &other );

      SelfType operator++( int )
      {
         SelfType temp( *this );
         ++*this;
         return temp;
      }

      SelfType operator--( int )
      {
         SelfType temp( *this );
         --*this;
         return temp;
      }

      SelfType &operator--()
      {
         decrement();
         return *this;
      }

      SelfType &operator++()
      {
         increment();
         return *this;
      }

      reference operator *() const
      {
         return deref();
      }
   };


   /** \brief Experimental and untested: iterator for object and array value.
    */
   class ValueIterator : public ValueIteratorBase
   {
   public:
      typedef unsigned int size_t;
      typedef int difference_type;
      typedef Value &reference;
      typedef Value *pointer;
      typedef ValueIterator SelfType;

      ValueIterator();
      ValueIterator( const ValueConstIterator &other );
      ValueIterator( const ValueIterator &other );
      /*! \internal Use by Value to create an iterator.
       */
      explicit ValueIterator( const Value::ObjectValues::iterator &current );

      SelfType &operator =( const SelfType &other );

      SelfType operator++( int )
      {
         SelfType temp( *this );
         ++*this;
         return temp;
      }

      SelfType operator--( int )
      {
         SelfType temp( *this );
         --*this;
         return temp;
      }

      SelfType &operator--()
      {
         decrement();
         return *this;
      }

      SelfType &operator++()
      {
         increment();
         return *this;
      }

      reference operator *() const
      {
         return deref();
      }
   };



   /** \brief Experimental and untested: represents an element of the "path" to access a node.
    */
   class PathArgument
   {
   public:
      friend class Path;

      PathArgument();
      PathArgument( Value::UInt index );
      PathArgument( const char *key );
      PathArgument( const std::string &key );

   private:
      enum Kind
      {
         kindNone = 0,
         kindIndex,
         kindKey
      };
      std::string key_;
      Value::UInt index_;
      Kind kind_;
   };

   /** \brief Experimental and untested: represents a "path" to access a node.
    *
    * Syntax:
    * - "." => root node
    * - ".[n]" => elements at index 'n' of root node (an array value)
    * - ".name" => member named 'name' of root node (an object value)
    * - ".name1.name2.name3"
    * - ".[0][1][2].name1[3]"
    * - ".%" => member name is provided as parameter
    * - ".[%]" => index is provied as parameter
    */
   class Path
   {
   public:
      Path( const std::string &path,
            const PathArgument &a1 = PathArgument(),
            const PathArgument &a2 = PathArgument(),
            const PathArgument &a3 = PathArgument(),
            const PathArgument &a4 = PathArgument(),
            const PathArgument &a5 = PathArgument() );

      const Value &resolve( const Value &root ) const;
      Value resolve( const Value &root, 
                     const Value &defaultValue ) const;
      /// Creates the "path" to access the specified node and returns a reference on the node.
      Value &make( Value &root ) const;

   private:
      typedef std::vector<const PathArgument *> InArgs;
      typedef std::vector<PathArgument> Args;

      void makePath( const std::string &path,
                     const InArgs &in );
      void addPathInArg( const std::string &path, 
                         const InArgs &in, 
                         InArgs::const_iterator &itInArg, 
                         PathArgument::Kind kind );
      void invalidPath( const std::string &path, 
                        int location );

      Args args_;
   };

} // namespace Json


#endif // CPPTL_JSON_H_INCLUDED
