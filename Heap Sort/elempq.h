#ifndef _ELEMPQ_H
#define _ELEMPQ_H

template<class T, class P>
class Elem
{
public:

	typedef T value_type;
	typedef P priority;

	Elem();
	Elem(const Elem<T, P>&);
	Elem(const value_type&, const priority&);
	~Elem();

	Elem<T, P>& operator =(const Elem<T, P>&);
	bool operator ==(const Elem<T, P>&) const;
	bool operator !=(const Elem<T, P>&) const;
	bool operator >(const Elem<T, P>&) const;
	bool operator <(const Elem<T, P>&) const;

	void setValue(const value_type&);
	value_type getValue() const;
	void setPriority(const priority&);
	priority getPriority() const;

private:
	value_type value;
	priority prior;
};

template<class T, class P>
ostream& operator <<(ostream& out, const Elem<T, P>& elem)
{
	out << elem.getValue() << " (" << elem.getPriority() << ")";
	return out;
}

template<class T, class P>
Elem<T, P>::Elem()
{
	value = value_type();
	prior = priority();
}

template<class T, class P>
Elem<T,P>::Elem(const Elem<T, P>& el2)
{
	*this = el2;
}

template<class T, class P>
Elem<T, P>::Elem(const value_type& val, const priority& pri)
{
	value = val;
	prior = pri;
}

template<class T, class P>
Elem<T, P>::~Elem()
{
	value = value_type();
	prior = priority();
}

template<class T, class P>
Elem<T, P>& Elem<T, P>::operator =(const Elem<T, P>& elem2)
{
	if (&elem2 != this) // avoid auto-assignment
	{
		this->setValue(elem2.getValue());
		this->setPriority(elem2.getPriority());
	}
	return *this;
}

template<class T, class P>
bool Elem<T, P>::operator ==(const Elem<T, P>& elem2) const
{
	if (this->getValue() != elem2.getValue())
		return false;

	if (this->getPriority() != elem2.getPriority())
		return false;

	return true;
}

template<class T, class P>
bool Elem<T, P>::operator !=(const Elem<T, P>& elem2) const
{
	return (!(*this == elem2));
}
template<class T, class P>
bool Elem<T, P>::operator >(const Elem<T, P>& elem2) const
{
	return (this->getPriority() > elem2.getPriority());
}

template<class T, class P>
bool Elem<T, P>::operator <(const Elem<T, P>& elem2) const
{
	return (this->getPriority() < elem2.getPriority());
}

template<class T, class P>
void Elem<T, P>::setValue(const value_type& element)
{
	value = element;
}

template<class T, class P>
typename Elem<T, P>::value_type Elem<T, P>::getValue() const
{
	return value;
}

template<class T, class P>
void Elem<T, P>::setPriority(const priority& pri)
{
	prior = pri;
}

template<class T, class P>
typename Elem<T, P>::priority Elem<T, P>::getPriority() const
{
	return prior;
}

#endif // _ELEMPQ_H
