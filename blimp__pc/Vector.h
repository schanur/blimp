#ifndef __VECTOR_H__
#define __VECTOR_H__

class Vector {
	public:
		Vector (const double dInitXValue, 
				const double dInitYValue,
				const double dInitZValue);
		Vector ();

	private:
		void initValues (const double dInitXValue, 
				const double dInitYValue,
				const double dInitZValue);

		double dX, dY, dZ;
};

#endif
