#ifndef __FX_h__
#define __FX_h__

 /* Apple OSX */
/*#if defined(__APPLE__)
#define isnanf(X) isnan(X)
#if (__GNUC__ >= 4)
#define isnan(X) __inline_isnan(X)
#else
#define isnan(X) __isnan(X)
#endif
#endif
*/

#if WIN32 || __i386__
#define DENORMALIZE(fv) (fv<.00000001f && fv>-.00000001f)?0:(fv)
#else
#define DENORMALIZE(fv) (isnan (fv) ? 0.f : fv)
#endif
#define	PI	3.14159265358979323846f

class delay		// non-interpolating delay
{
public:
	delay(int buflen, bool interpolate);
	~delay();
	void	set_delay(float dtime);
	void	set_samplerate(float samplerate);
	void	flood(float value);
	float	clock(float input);
	void	report();
protected:
	float	*buffer;
	int		p_buflen;
	bool	interp;
	float	offset;
	float	samplerate;
	int		readp,readp2,writep;

	float	outPointer;
	float	alpha,alpha2,alpha3,omAlpha,coeff,lag,lastIn;
	float	ym1;
	float	y0;
	float	y1;
	float	y2;
};

class lfo
{
public:
	lfo();
	~lfo(){};
	float clock();
	void	set_samplerate(float samplerate);
	void	set_rate(float srate,int type);	// Hz; type: 0=sin, 1=tri
	void	set_phase(float phase);
	float	get_rate();
private:
	int		my_type;
	float	output;
	float	samplerate;
	float	inc;
	int		dir;
	float	c,s,ci,si,nc,ns;
	float	my_srate;
};

class filt1
{
	friend class filt_lp;
public:
	filt1();
	~filt1(){};
	float	lp();
	float	bp();
	float	hp();
	void	clock(float input);
	void	setparam(float cutoff, float q, float samplerate);
	void	set_samplerate(float samplerate);
private:
	float	fs;		// sampling freq
	float	fc;		// cutoff freq
	float	q;		// resonance
	float	m_f,m_q,m_qnrm;
	float	m_h;	// hp out
	float	m_b;	// bp out
	float	m_l;	// lp out
};

class filt_lp : public filt1
{
public:
	filt_lp();
	float	clock(float input);
};

#endif
