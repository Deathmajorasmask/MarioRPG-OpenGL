#ifndef _OpenMove
#define _OpenMove

class OpenMove {
public:
	OpenMove();
	~OpenMove();

	static void traslate(float, float, float);
	static void scale(float, float, float);
	static void rotate(float, int, int, int);

	static void multMat(float *, float *);
};

#endif
