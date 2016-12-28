#ifndef __SIGNUM_H__
#define __SIGNUM_H__

template <class IntType>
int8_t signum (IntType a);

template <class IntType>
int8_t signum (IntType a)
{
	if (a > 0) {
		return (1);
	} else if (a < 0) {
		return (-1);
	} else {
		return (0);
	}
}

#endif
