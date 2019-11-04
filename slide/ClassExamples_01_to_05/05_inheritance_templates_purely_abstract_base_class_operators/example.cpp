//This example uses:
//-templates
//-purely abstract base class
//-STL-containers
//-STL I/O functions
//-operators
//-const correctness (we will see more about this later, don't worry if you do not understand all the const-business now)
//
//Note: NamedContainer serves as a base class for giving a name to a container, and also for having a
//      abstract interface to different containers, such that we can treat them in the same way. Child classes
//      are a NamedList and a NamedVector.
//
//Note: Ideally, we would again like to split things up into different files, I was lazy for this example

#include <iostream>
#include <vector>
#include <list>

template<typename T>
class NamedContainer {
public:
  NamedContainer( const std::string& name );
  virtual ~NamedContainer();

  virtual void push_back( T& value ) = 0;
  virtual T& at( int index ) = 0;
  virtual const T& at( int index ) const = 0;
  virtual int size() const = 0;
  std::string& name();

private:
  std::string _s_name;
};

template<typename T>
NamedContainer<T>::NamedContainer( const std::string& name ) {
  _s_name = name;
}

template<typename T>
NamedContainer<T>::~NamedContainer()
{}

template<typename T>
std::string&
NamedContainer<T>::name() {
  return _s_name;
}

template<typename T>
class NamedList : public NamedContainer<T> {
public:
  NamedList( const std::string& name );
  virtual ~NamedList();

  virtual void push_back( T& value );
  virtual T& at( int index );
  virtual const T& at( int index ) const;
  virtual int size() const;

  NamedList<T> operator+( const NamedList<T> & rhs );
  NamedList<T> operator-( const NamedList<T> & rhs );
  void operator=( const NamedList<T> & rhs );

private:
  std::list<T> _data;
};

template<typename T>
NamedList<T>::NamedList( const std::string & name ) : NamedContainer<T>(name)
{}

template<typename T>
NamedList<T>::~NamedList()
{}

template<typename T>
void
NamedList<T>::push_back( T& value ) {
  _data.push_back(value);
}

template<typename T>
T&
NamedList<T>::at( int index ) {
  if( index >= _data.size() ) {
    std::cout << "Error in NamedList: Attempted access beyond container size\n";
    return *(_data.begin());
  }
  typename std::list<T>::iterator it = _data.begin();
  for( int i = 0; i < index; i++ )
    it++;
  return *it;
}

template<typename T>
const T&
NamedList<T>::at( int index ) const {
  if( index >= _data.size() ) {
    std::cout << "Error in NamedList: Attempted access beyond container size\n";
    return *(_data.begin());
  }
  typename std::list<T>::const_iterator it = _data.begin();
  for( int i = 0; i < index; i++ )
    it++;
  return *it;
}

template<typename T>
int
NamedList<T>::size() const {
  return _data.size();
}

template<typename T>
NamedList<T>
NamedList<T>::operator+( const NamedList<T> & rhs ) {
  if( this->size() != rhs.size() ) {
    std::cout << "Error in NamedList: Attempted to add a list that has different length\n";
    return NamedList<T>(*this);
  }
  NamedList<T> copy(*this);
  for( int i = 0; i < this->size(); i++ )
    copy.at(i) += rhs.at(i);

  return copy;
}

template<typename T>
NamedList<T>
NamedList<T>::operator-( const NamedList<T> & rhs ) {
  if( this->size() != rhs.size() ) {
    std::cout << "Error in NamedList: Attempted to add a list that has different length\n";
    return NamedList<T>(*this);
  }
  NamedList<T> copy(*this);
  for( int i = 0; i < this->size(); i++ )
    copy.at(i) -= rhs.at(i);

  return copy;
}

template<typename T>
void
NamedList<T>::operator=( const NamedList<T> & rhs ) {
  this->_data = rhs._data;
}

template<typename T>
class NamedVector : public NamedContainer<T> {
public:
  NamedVector( const std::string& name );
  virtual ~NamedVector();

  virtual void push_back( T& value );
  virtual T& at( int index );
  virtual const T& at( int index ) const;
  virtual int size() const;

  NamedVector<T> operator+( const NamedVector<T> & rhs );
  NamedVector<T> operator-( const NamedVector<T> & rhs );
  void operator=( const NamedVector<T> & rhs );

private:
  std::vector<T> _data;
};

template<typename T>
NamedVector<T>::NamedVector( const std::string & name ) : NamedContainer<T>(name)
{}

template<typename T>
NamedVector<T>::~NamedVector()
{}

template<typename T>
void
NamedVector<T>::push_back( T& value ) {
  _data.push_back(value);
}

template<typename T>
T&
NamedVector<T>::at( int index ) {
  if( index >= _data.size() ) {
    std::cout << "Error in NamedVector: Attempted access beyond container size\n";
    return *(_data.begin());
  }
  return _data.at(index);
}

template<typename T>
const T&
NamedVector<T>::at( int index ) const {
  if( index >= _data.size() ) {
    std::cout << "Error in NamedVector: Attempted access beyond container size\n";
    return *(_data.begin());
  }
  return _data.at(index);
}

template<typename T>
int
NamedVector<T>::size() const {
  return _data.size();
}

template<typename T>
NamedVector<T>
NamedVector<T>::operator+( const NamedVector<T> & rhs ) {
  if( this->size() != rhs.size() ) {
    std::cout << "Error in NamedVector: Attempted to add a list that has different length\n";
    return NamedVector<T>(*this);
  }
  NamedVector<T> copy(*this);
  for( int i = 0; i < this->size(); i++ )
    copy.at(i) += rhs.at(i);

  return copy;
}

template<typename T>
NamedVector<T>
NamedVector<T>::operator-( const NamedVector<T> & rhs ) {
  if( this->size() != rhs.size() ) {
    std::cout << "Error in NamedVector: Attempted to add a list that has different length\n";
    return NamedVector<T>(*this);
  }
  NamedVector<T> copy(*this);
  for( int i = 0; i < this->size(); i++ )
    copy.at(i) -= rhs.at(i);

  return copy;
}

template<typename T>
void
NamedVector<T>::operator=( const NamedVector<T> & rhs ) {
  this->_data = rhs._data;
}

int main() {
  //create a few named lists
  NamedList<int> list1(std::string("list1"));
  NamedList<int> list2(std::string("list2"));
  for( int i = 0; i < 10; i++ ) {
    list1.push_back(i);
    list2.push_back(i);
  }

  //demonstrate use of addition and assignment operator
  NamedList<int> list3( std::string("list3") );
  list3 = list1 + list2;

  //create a few named vectors
  NamedVector<int> vector1(std::string("vector1"));
  NamedVector<int> vector2(std::string("vector2"));
  for( int i = 0; i < 10; i++ ) {
    vector1.push_back(i);
    vector2.push_back(i);
  }

  //demonstrate use of subtraction and assignment operator
  NamedVector<int> vector3( std::string("vector3") );
  vector3 = vector1 - vector2;

  //treat all of the containers equally, store them in a vector
  std::vector<NamedContainer<int>*> allMyContainers;
  allMyContainers.push_back(&list1);
  allMyContainers.push_back(&list2);
  allMyContainers.push_back(&list3);
  allMyContainers.push_back(&vector1);
  allMyContainers.push_back(&vector2);
  allMyContainers.push_back(&vector3);

  //Loop through all containers and print their name and their contents
  for( int i = 0; i < allMyContainers.size(); i++ ) {
    std::cout << "Printing content of container named " << allMyContainers[i]->name() << "\n";
    for( int j = 0; j < allMyContainers[i]->size(); j++ )
      std::cout << allMyContainers[i]->at(j) << " ";
    std::cout << "\n\n";
  }

  return 0;
}