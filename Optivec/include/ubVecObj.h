/* ubVecObj.H

  object-oriented interface for OptiVec vector functions
  of type "unsigned byte"

  This file was written by Brian Dale, Case Western Reserve Univ.

  Copyright (c) 1996-2017 by OptiCode
  All Rights Reserved.
*/

#ifndef UBVECOBJ_H

#include <VecObj.h>
#include <uiVecObj.h>

#define t    unsigned char
#define cvta const vector<t>&
#define cmta const matrix<unsigned char>&
#define cuia const ui&
#define cta  const t&

#define vta  vector<t>&
#define uia  ui&
#define ta   t&

#define vt   vector<t>
#define tVector ubVector

#define tVecObj ubVecObj
#ifdef __BORLANDC__
#pragma warn -inl
#endif

#if defined _MSC_VER || (defined __BORLANDC__ && __BORLANDC__ >= 0x500)
namespace OptiVec{
#endif

	VECOBJ_NEW_TEMPLATE class vector<t>
	{
#ifdef _MSC_VER 
     public:
		tVector vx_vect;
		ui      ui_size;
#else
		tVector vx_vect;
		ui      ui_size;
		friend class vector<char>;
		friend class vector<short>;
		friend class vector<int>;
		friend class vector<long>;
		friend class vector<quad>;
		friend class vector<unsigned char>;
		friend class vector<unsigned short>;
		friend class vector<unsigned int>;
		friend class vector<unsigned long>;
		#if defined _WIN64
			friend class vector<uquad>;
		#endif
		friend class vector<ui>;
		friend class vector<float>;
		friend class vector<double>;
		friend class vector<extended>;
		friend class vector<fComplex>;
		friend class vector<dComplex>;
		friend class vector<eComplex>;
		friend class vector<fPolar>;
		friend class vector<dPolar>;
		friend class vector<ePolar>;
		friend class matrix<char>;
		friend class matrix<short>;
		friend class matrix<int>;
		friend class matrix<long>;
		friend class matrix<quad>;
		friend class matrix<unsigned char>;
		friend class matrix<unsigned short>;
		friend class matrix<unsigned int>;
		friend class matrix<unsigned long>;
		#if defined _WIN64
			friend class matrix<uquad>;
		#endif
		friend class matrix<float>;
		friend class matrix<double>;
		friend class matrix<extended>;
		friend class matrix<fComplex>;
		friend class matrix<dComplex>;
		friend class matrix<eComplex>;
#endif
	public:
////////////////////////////////////////////////////////////////////////////////////////////////////
//constructors and destructors
//
		vector(){	vx_vect=0;	ui_size=0;}

		vector(cuia size)
		{	if(size){	vx_vect= VUB_vector(size);	ui_size= size;}
			else{	vx_vect= 0;	ui_size= 0;}}

		vector(cuia size, cta fill)
		{	if(!size) //size == 0
			{	vx_vect=0;	ui_size=0;}
			else if(!fill) //fill == 0.0
			{	vx_vect= VUB_vector0(size);	ui_size= size;}
			else
			{	vx_vect= VUB_vector(size);	ui_size= size;	VUB_equC(vx_vect,ui_size,fill);}}

		vector(cvta init)
		{	if(init.ui_size)
			{ vx_vect= VUB_vector(init.ui_size);	ui_size= init.ui_size;	VUB_equV(vx_vect, init.vx_vect, ui_size);}
			else
			{	vx_vect=0;	ui_size=0;}}

		~vector(){	if(vx_vect) V_free(vx_vect);}


////////////////////////////////////////////////////////////////////////////////////////////////////
//management
//
		void enforceSize()const{ if(!ui_size) throw OptiVec_EmptySizeErr();}

		void enforceSize(ui size)const{ if(ui_size != size) throw OptiVec_SizeErr();}

		void enforcePow2()const{ if(!ui_isipow2(ui_size)) throw OptiVec_Pow2SizeErr();}

		void setSize(cuia size)
		{	if(!size) dealloc(); //can set size to zero
			if(ui_size != size) //only allocate if different sizes
			{	if(vx_vect) V_free(vx_vect);
				vx_vect= VUB_vector(size);
				ui_size= size;}}

		void setSize(cvta X)
		{	if(!X.ui_size) dealloc(); //can set size to zero
			if(ui_size != X.ui_size) //only allocate if different sizes
			{	if(vx_vect) V_free(vx_vect);
				vx_vect= VUB_vector(X.ui_size);
				ui_size= X.ui_size;}}

		ui       getSize() const { return ui_size; }
		tVector  getVector() const { return vx_vect; }

#if !defined (_CRTDBG_MAP_ALLOC) // crtdbg.h defines free as a macro
		void free()
		{	if(vx_vect) V_free(vx_vect);
			vx_vect=0;
			ui_size=0;}
#endif

		void dealloc()
		{	if(vx_vect) V_free(vx_vect);
			vx_vect=0;
			ui_size=0;}

		ta at(ui n)const
		{	enforceSize();
			if(ui_size<=n) throw OptiVec_SmallSizeErr();
			return vx_vect[n];}


///////////////////////////////////////////////////////////////////////////////////////////////////
// Overloaded operators
//
		vta operator=(cvta vect)
		{	setSize(vect.ui_size);
			enforceSize();
			VUB_equV(vx_vect, vect.vx_vect, ui_size);
			return *this;}

		vta operator=(cta scalar)
		{	enforceSize();
			VUB_equC(vx_vect, ui_size, scalar);
			return *this;}

		//this is the only really dangerous operator
		ta operator[](const int& index){return vx_vect[index];}

		vta operator+=(cvta X)
		{	enforceSize();
			VUB_accV(vx_vect, X.vx_vect, ui_size);
			return *this;}

		vta operator+=(cta scalar)
		{	enforceSize();
			VUB_addC(vx_vect, vx_vect, ui_size, scalar);
			return *this;}

		vta operator*=(cvta X)
		{	enforceSize();
			VUB_mulV(vx_vect, vx_vect, X.vx_vect, ui_size);
			return *this;}

		vta operator*=(cta scalar)
		{	enforceSize();
			VUB_mulC(vx_vect,vx_vect,ui_size,scalar);
			return *this;}

		vt operator+(cvta rhs)
		{	tVecObj tmp((this->ui_size<rhs.ui_size) ? this->ui_size : rhs.ui_size);
			tmp.enforceSize();
			VUB_addV(tmp.vx_vect,this->vx_vect,rhs.vx_vect,tmp.ui_size);
			return tmp;}

		vt operator+(cta C)
		{	tVecObj tmp(this->ui_size);
			tmp.enforceSize();
			VUB_addC(tmp.vx_vect,this->vx_vect,tmp.ui_size,C);
			return tmp;}

		friend vt operator+(cta C, cvta X)
		{	tVecObj tmp(X.ui_size);
			tmp.enforceSize();
			VUB_addC(tmp.vx_vect,X.vx_vect,tmp.ui_size,C);
			return tmp;}

		vt operator-(cvta rhs)
		{	tVecObj tmp((this->ui_size<rhs.ui_size) ? this->ui_size : rhs.ui_size);
			tmp.enforceSize();
			VUB_subV(tmp.vx_vect,this->vx_vect,rhs.vx_vect,tmp.ui_size);
			return tmp;}

		vt operator-(cta C)
		{	tVecObj tmp(this->ui_size);
			tmp.enforceSize();
			VUB_subC(tmp.vx_vect,this->vx_vect,tmp.ui_size,C);
			return tmp;}

		friend vt operator-(cta C, cvta X)
		{	tVecObj tmp(X.ui_size);
			tmp.enforceSize();
			VUB_subrC(tmp.vx_vect,X.vx_vect,tmp.ui_size,C);
			return tmp;}

		vt operator*(cvta rhs)
		{	tVecObj tmp((this->ui_size<rhs.ui_size) ? this->ui_size : rhs.ui_size);
			tmp.enforceSize();
			VUB_mulV(tmp.vx_vect,this->vx_vect,rhs.vx_vect,tmp.ui_size);
			return tmp;}

		vt operator*(cta C)
		{	tVecObj tmp(this->ui_size);
			tmp.enforceSize();
			VUB_mulC(tmp.vx_vect,this->vx_vect,tmp.ui_size,C);
			return tmp;}

		friend vt operator*(cta C, cvta X)
		{	tVecObj tmp(X.ui_size);
			tmp.enforceSize();
			VUB_mulC(tmp.vx_vect,X.vx_vect,tmp.ui_size,C);
			return tmp;}

		vt operator/(cvta rhs)
		{	tVecObj tmp((this->ui_size<rhs.ui_size) ? this->ui_size : rhs.ui_size);
			tmp.enforceSize();
			VUB_divV(tmp.vx_vect,this->vx_vect,rhs.vx_vect,tmp.ui_size);
			return tmp;}

		vt operator/(cta C)
		{	tVecObj tmp(this->ui_size);
			tmp.enforceSize();
			VUB_divC(tmp.vx_vect,this->vx_vect,tmp.ui_size,C);
			return tmp;}

		friend vt operator/(cta C, cvta X)
		{	tVecObj tmp(X.ui_size);
			tmp.enforceSize();
			VUB_divrC(tmp.vx_vect,X.vx_vect,tmp.ui_size,C);
			return tmp;}


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//OptiVec functions in member format
//

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//from VXstd.h
//

/////////////////////////////////////////////////////////////////////////////////////////
//Generation
//

		//these are not recommended, better to use constructors
		void _vector(ui size) //underscore necessary to avoid confusing with constructor
		{
			dealloc();
			if(size) vx_vect= VUB_vector(size);
			ui_size=size;
		}

		void vector0(ui size)
		{
			dealloc();
			if(size) vx_vect= VUB_vector0(size);
			ui_size=size;
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Addressing single vector elements
//
		t* Pelement(ui n)const
		{
			enforceSize();
			if(ui_size<=n) throw OptiVec_SmallSizeErr();
			return VUB_Pelement(vx_vect,n);
		}

		t element(ui n)const
		{
			enforceSize();
			if(ui_size<=n) throw OptiVec_SmallSizeErr();
			return VUB_element(vx_vect,n);
		}

		void getElement(t *y, ui n)
		{
			enforceSize();
			if(ui_size<=n) throw OptiVec_SmallSizeErr();
			return VUB_getElement(y,vx_vect,n);
		}

		void setElement(ui n, cta C)
		{
			if(ui_size<=n) throw OptiVec_SmallSizeErr();
			VUB_setElement(vx_vect,n, C);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Initialization
//

		void equ0()
		{
			enforceSize();
			VUB_equ0(vx_vect,ui_size);
		}

		void equC(cta C)
		{
			enforceSize();
			VUB_equC(vx_vect, ui_size, C);
		}

		void equV(cvta X)
		{
			enforceSize();
			VUB_equV(vx_vect, X.vx_vect, ui_size);
		}

		void ramp(cta Start, cta Rise)
		{
			enforceSize();
			VUB_ramp(vx_vect, ui_size, Start, Rise);
		}

		long random(const long& seed, cta Min, cta Max)
		{
			enforceSize();
			return VUB_random(vx_vect, ui_size, seed, Min, Max);
		}

		void randomLC(const long& seed, cta Min, cta Max, V_RANDOMLCSTATE *state)
		{
			enforceSize();
			VUB_randomLC(vx_vect, ui_size, seed, Min, Max, state);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Data-type interconversions
//
		//defined by including biVecObj.h
		void BItoUB(const biVecObj& X);
		//defined by including usVecObj.h
		void UStoUB(const usVecObj& X);
		//defined by including uVecObj.h
		void UtoUB(const uVecObj& X);
		//defined by including ulVecObj.h
		void ULtoUB(const ulVecObj& X);
		#if defined _WIN64
			//defined by including uqVecObj.h
			void UQtoUB(const uqVecObj& X);
		#endif


/////////////////////////////////////////////////////////////////////////////////////////
//Index-oriented manipulations
//
		void reflect()
		{
			enforceSize();
			VUB_reflect(vx_vect, ui_size);
		}

		void rev(cvta X)
		{
			enforceSize();
			VUB_rev(vx_vect, X.vx_vect, ui_size);
		}

		void rotate( cvta X, ssize_t pos )
		{
			enforceSize();
			VUB_rotate(vx_vect, X.vx_vect, ui_size, pos);
		}

		void rotate_buf( cvta X, ssize_t pos, cvta Buf )
		{
			enforceSize();
			VUB_rotate_buf(vx_vect, X.vx_vect, ui_size, pos, Buf.vx_vect);
		}


		void _delete(ui pos)
		{
			enforceSize();
			if(ui_size<=pos) throw OptiVec_SmallSizeErr();
			VUB_delete(vx_vect, ui_size, pos);
		}

		void insert(ui pos, cta C)
		{
			enforceSize();
			if(ui_size<=pos) throw OptiVec_SmallSizeErr();
			VUB_insert(vx_vect, ui_size, pos, C);
		}

		void sort(cvta X, int dir=1)
		{
			enforceSize();
			VUB_sort(vx_vect,X.vx_vect,ui_size,dir);
		}

		//sortind member of uiVecObj

		void subvector(cvta X, ssize_t step, ui start=0)
		{
			enforceSize();
			if(vx_vect==X.vx_vect) throw OptiVec_Err();
			VUB_subvector(vx_vect, ui_size, X.vx_vect+start, step);
		}

		void subvector_equC(const ui& samp, cta C)
		{
			enforceSize();
			VUB_subvector_equC(vx_vect,1+(ui_size-1)/samp,samp,C);
		}

		void subvector_equV(const ui& samp, cvta X)
		{
			enforceSize();
			VUB_subvector_equV(vx_vect,1+(ui_size-1)/samp,samp,X.vx_vect);
		}

		void indpick(const uiVecObj& Ind, cvta X)
		{
			enforceSize();
			VUB_indpick(vx_vect, Ind.vx_vect, ui_size, X.vx_vect);
		}

		void indput(cvta X, const uiVecObj& Ind)
		{
			enforceSize();
			X.enforceSize();
			VUB_indput(vx_vect,X.vx_vect,Ind.vx_vect,X.ui_size);
		}

		ui searchC(cta C, int mode=0) const
		{
			enforceSize();
			return VUB_searchC(vx_vect, ui_size, C, mode);
		}

		//searchV member of uiVecObj


/////////////////////////////////////////////////////////////////////////////////////////
//Functions of a sub-set of elements
//


/////////////////////////////////////////////////////////////////////////////////////////
//One-Dimensional Vector Operations
//

		t sum() const
		{
			enforceSize();
			return VUB_sum(vx_vect, ui_size);
		}

		void runsum(cvta X)
		{
			enforceSize();
			VUB_runsum(vx_vect, X.vx_vect, ui_size);
		}

		//underscore needed because max defined in windef.h
		t _max() const
		{
			enforceSize();
			return VUB_max(vx_vect, ui_size);
		}

		//underscore needed because min defined in windef.h
		t _min() const
		{
			enforceSize();
			return VUB_min(vx_vect, ui_size);
		}

		t maxind(ui* Ind) const
		{
			enforceSize();
			return VUB_maxind(Ind, vx_vect, ui_size);
		}

		t minind(ui* Ind) const
		{
			enforceSize();
			return VUB_minind(Ind, vx_vect, ui_size);
		}

		double fsum() const
		{
			enforceSize();
			return VUB_fsum(vx_vect,ui_size);
		}

		double mean() const
		{
			enforceSize();
			return VUB_mean(vx_vect,ui_size);
		}

		void runmax(cvta X)
		{
			enforceSize();
			VUB_runmax(vx_vect, X.vx_vect, ui_size);
		}

		void runmin(cvta X)
		{
			enforceSize();
			VUB_runmin(vx_vect, X.vx_vect, ui_size);
		}

		int iselementC(cta C) const
		{
			enforceSize();
			return VUB_iselementC(vx_vect, ui_size, C);
		}

		ui iselementV(cvta X, cvta Tab)
		{
			enforceSize();
			return VUB_iselementV(vx_vect, X.vx_vect,
				ui_size, Tab.vx_vect, Tab.ui_size);
		}

		//distribution member of uiVecObj


/////////////////////////////////////////////////////////////////////////////////////////
//Statistical Functions and Building Blocks
//


/////////////////////////////////////////////////////////////////////////////////////////
//Fourier Transforms, Convolutions, Filtering
//


/////////////////////////////////////////////////////////////////////////////////////////
//Analysis
//


/////////////////////////////////////////////////////////////////////////////////////////
//Geometrical Vector Arithmetics
//


/////////////////////////////////////////////////////////////////////////////////////////
//Input and Output
//
		void fprint(FILE* stream, unsigned nperline, unsigned linewidth) const
		{
			enforceSize();
			VUB_fprint(stream,vx_vect,ui_size,nperline,linewidth);
		}

		void cprint(unsigned nperline) const
		{
			enforceSize();
			VUB_cprint(vx_vect,ui_size,nperline);
		}

		void print(unsigned nperline) const
		{
			fprint(stdout,nperline,80);
		}

		void setRadix(int i)
		{
			V_setRadix(i);
		}

		void read(FILE* stream)
		{
			enforceSize();
			VUB_read(vx_vect,ui_size,stream);
		}

		void write(FILE* stream) const
		{
			enforceSize();
			VUB_write(stream,vx_vect,ui_size);
		}

//nread
//nwrite

		void setWriteFormat(char* formatString) const
		{
			VUB_setWriteFormat(formatString);
		}

		void setWriteSeparate(char* sepString) const
		{
			VUB_setWriteSeparate(sepString);
		}

//setNWriteSeparate

		void store(FILE* stream) const
		{
			enforceSize();
			fwrite(&ui_size,sizeof(ui),1,stream);
			VUB_store(stream,vx_vect,ui_size);
		}

		void recall(FILE* stream)
		{
			ui sz;
			fread(&sz,sizeof(ui),1,stream);
			setSize(sz);
			VUB_recall(vx_vect,ui_size,stream);
		}


/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//from VXmath.h
//


/////////////////////////////////////////////////////////////////////////////////////////
//Rounding
//
		//defined by including fVecObj.h
		int roundtoUB(const fVecObj& X);

		//defined by including fVecObj.h
		int floortoUB(const fVecObj& X);
		
		//defined by including fVecObj.h
		int ceiltoUB(const fVecObj& X);
		
		//defined by including fVecObj.h
		int choptoUB(const fVecObj& X);
		
		int trunctoUB(const fVecObj& X)
		{
			return choptoUB(X);
		}
		
		//defined by including dVecObj.h
		int roundtoUB(const dVecObj& X);
		
		//defined by including dVecObj.h
		int floortoUB(const dVecObj& X);
		
		//defined by including dVecObj.h
		int ceiltoUB(const dVecObj& X);
		
		//defined by including dVecObj.h
		int choptoUB(const dVecObj& X);
		
		int trunctoUB(const dVecObj& X)
		{
			return choptoUB(X);
		}

#if (defined __BORLANDC__) && !(defined _WIN64) //80-bit numbers supported
		//defined by including eVecObj.h
		int roundtoUB(const eVecObj& X);
		
		//defined by including eVecObj.h
		int floortoUB(const eVecObj& X);
		
		//defined by including eVecObj.h
		int ceiltoUB(const eVecObj& X);
		
		//defined by including eVecObj.h
		int choptoUB(const eVecObj& X);
		
		int trunctoUB(const eVecObj& X)
		{
			return choptoUB(X);
		}
#endif //__BORLANDC__



/////////////////////////////////////////////////////////////////////////////////////////
//Comparisons
//
		ui cmp_eq0(cvta X)
		{
			enforceSize();
			return VUB_cmp_eq0(vx_vect,X.vx_vect,ui_size);
		}

		ui cmp_ne0(cvta X)
		{
			enforceSize();
			return VUB_cmp_ne0(vx_vect,X.vx_vect,ui_size);
		}

		ui cmp_gt0(cvta X)
		{
			enforceSize();
			return VUB_cmp_gt0(vx_vect,X.vx_vect,ui_size);
		}

		ui cmp_eqC(cvta X, cta C)
		{
			enforceSize();
			return VUB_cmp_eqC(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_neC(cvta X, cta C)
		{
			enforceSize();
			return VUB_cmp_neC(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_leC(cvta X, cta C)
		{
			enforceSize();
			return VUB_cmp_leC(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_ltC(cvta X, cta C)
		{
			enforceSize();
			return VUB_cmp_ltC(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_geC(cvta X, cta C)
		{
			enforceSize();
			return VUB_cmp_geC(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_gtC(cvta X, cta C)
		{
			enforceSize();
			return VUB_cmp_gtC(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_eqV(cvta X, cvta Y)
		{
			enforceSize();
			return VUB_cmp_eqV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		ui cmp_neV(cvta X, cvta Y)
		{
			enforceSize();
			return VUB_cmp_neV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		ui cmp_leV(cvta X, cvta Y)
		{
			enforceSize();
			return VUB_cmp_leV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		ui cmp_ltV(cvta X, cvta Y)
		{
			enforceSize();
			return VUB_cmp_ltV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		ui cmp_geV(cvta X, cvta Y)
		{
			enforceSize();
			return VUB_cmp_geV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		ui cmp_gtV(cvta X, cvta Y)
		{
			enforceSize();
			return VUB_cmp_gtV(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
		}

		ui cmp_exclrange0C(cvta X, cta C)
		{
			enforceSize();
			return VUB_cmp_exclrange0C(vx_vect,X.vx_vect,ui_size,C);
		}

		ui cmp_inclrangeCC(cvta X, cta CLo, cta CHi)
		{
			enforceSize();
			return VUB_cmp_inclrangeCC(vx_vect,X.vx_vect,ui_size,CLo,CHi);
		}

		ui cmp_exclrangeCC(cvta X, cta CLo, cta CHi)
		{
			enforceSize();
			return VUB_cmp_exclrangeCC(vx_vect,X.vx_vect,ui_size,CLo,CHi);
		}

		ui cnt_eq0()  const
		{
			enforceSize();
			return VUB_cnt_eq0(vx_vect, ui_size);
		}

		ui cnt_ne0()  const
		{
			enforceSize();
			return VUB_cnt_ne0(vx_vect, ui_size);
		}

		ui cnt_gt0()  const
		{
			enforceSize();
			return VUB_cnt_gt0(vx_vect, ui_size);
		}

		ui cnt_eqC(cta C) const
		{
			enforceSize();
			return VUB_cnt_eqC(vx_vect,ui_size,C);
		}

		ui cnt_neC(cta C) const
		{
			enforceSize();
			return VUB_cnt_neC(vx_vect,ui_size,C);
		}

		ui cnt_leC(cta C) const
		{
			enforceSize();
			return VUB_cnt_leC(vx_vect,ui_size,C);
		}

		ui cnt_ltC(cta C) const
		{
			enforceSize();
			return VUB_cnt_ltC(vx_vect,ui_size,C);
		}

		ui cnt_geC(cta C) const
		{
			enforceSize();
			return VUB_cnt_geC(vx_vect,ui_size,C);
		}

		ui cnt_gtC(cta C) const
		{
			enforceSize();
			return VUB_cnt_gtC(vx_vect,ui_size,C);
		}

		ui cnt_exclrange0C(cta C) const
		{
			enforceSize();
			return VUB_cnt_exclrange0C(vx_vect,ui_size,C);
		}

		ui cnt_inclrangeCC(cta CLo, cta CHi) const
		{
			enforceSize();
			return VUB_cnt_inclrangeCC(vx_vect,ui_size,CLo, CHi);
		}

		ui cnt_exclrangeCC(cta CLo, cta CHi) const
		{
			enforceSize();
			return VUB_cnt_exclrangeCC(vx_vect,ui_size,CLo, CHi);
		}

		ui cnt_eqV(cvta Y) const
		{
			enforceSize();
			return VUB_cnt_eqV(vx_vect,Y.vx_vect,ui_size);
		}

		ui cnt_neV(cvta Y) const
		{
			enforceSize();
			return VUB_cnt_neV(vx_vect,Y.vx_vect,ui_size);
		}

		ui cnt_leV(cvta Y) const
		{
			enforceSize();
			return VUB_cnt_leV(vx_vect,Y.vx_vect,ui_size);
		}

		ui cnt_ltV(cvta Y) const
		{
			enforceSize();
			return VUB_cnt_ltV(vx_vect,Y.vx_vect,ui_size);
		}

		ui cnt_geV(cvta Y) const
		{
			enforceSize();
			return VUB_cnt_geV(vx_vect,Y.vx_vect,ui_size);
		}

		ui cnt_gtV(cvta Y) const
		{
			enforceSize();
			return VUB_cnt_gtV(vx_vect,Y.vx_vect,ui_size);
		}

		//indexed comparisons are members of uiVecObj



/////////////////////////////////////////////////////////////////////////////////////////
//Standard Arithmetics or Basic Arithmetics
//

		void addC(cvta X, cta C)
		{
			enforceSize();
			VUB_addC(vx_vect, X.vx_vect, ui_size, C);
		}

		void subC(cvta X, cta C)
		{
			enforceSize();
			VUB_subC(vx_vect, X.vx_vect, ui_size, C);
		}

		void subrC(cvta X, cta C)
		{
			enforceSize();
			VUB_subrC(vx_vect, X.vx_vect, ui_size, C);
		}

		void mulC(cvta X, cta C)
		{
			enforceSize();
			VUB_mulC(vx_vect, X.vx_vect, ui_size, C);
		}

		void divC(cvta X, cta C)
		{
			enforceSize();
			VUB_divC(vx_vect, X.vx_vect, ui_size, C);
		}

		void divrC(cvta X, cta C)
		{
			enforceSize();
			VUB_divrC(vx_vect, X.vx_vect, ui_size, C);
		}

		void modC(cvta X, cta C)
		{
			enforceSize();
			VUB_modC(vx_vect, X.vx_vect, ui_size, C);
		}

		void maxC(cvta X, cta C)
		{
			enforceSize();
			VUB_maxC( vx_vect, X.vx_vect, ui_size, C);
		}

		void minC(cvta X, cta C)
		{
			enforceSize();
			VUB_minC( vx_vect, X.vx_vect, ui_size, C);
		}

		void addV(cvta X, cvta Y)
		{
			enforceSize();
			VUB_addV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void subV(cvta X, cvta Y)
		{
			enforceSize();
			VUB_subV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void subrV(cvta X, cvta Y)
		{
			enforceSize();
			VUB_subrV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void mulV(cvta X, cvta Y)
		{
			enforceSize();
			VUB_mulV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void divV(cvta X, cvta Y)
		{
			enforceSize();
			VUB_divV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void divrV(cvta X, cvta Y)
		{
			enforceSize();
			VUB_divrV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void modV(cvta X, cvta Y)
		{
			enforceSize();
			VUB_modV(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void maxV(cvta X, cvta Y)
		{
			enforceSize();
			VUB_maxV( vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}

		void minV(cvta X, cvta Y)
		{
			enforceSize();
			VUB_minV( vx_vect, X.vx_vect, Y.vx_vect, ui_size);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Accumulation
//
		void accV(cvta X)
		{
			enforceSize();
			VUB_accV(vx_vect,X.vx_vect,ui_size);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Bit-wise operations
//
		void shl(cvta X, unsigned C)
		{
			enforceSize();
			VUB_shl(vx_vect,X.vx_vect,ui_size,C);
		}

		void shr(cvta X, unsigned C)
		{
			enforceSize();
			VUB_shr(vx_vect,X.vx_vect,ui_size,C);
		}

		#if (defined __BORLANDC__) && (defined _WIN64 || defined __clang__) // cannot have function "and"
			void _and(cvta X, cta C)
		#else
			void and(cvta X, cta C)
		#endif
		{
			enforceSize();
			VUB_and(vx_vect,X.vx_vect,ui_size,C);
		}

		#if (defined __BORLANDC__) && (defined _WIN64 || defined __clang__) // cannot have function "or"
			void _or(cvta X, cta C)
		#else
			void or(cvta X, cta C)
		#endif
		{
			enforceSize();
			VUB_or(vx_vect,X.vx_vect,ui_size,C);
		}

		#if (defined __BORLANDC__) && (defined _WIN64 || defined __clang__) // cannot have function "xor"
			void _xor(cvta X, cta C)
		#else
			void xor(cvta X, cta C)
		#endif
		{
			enforceSize();
			VUB_xor(vx_vect,X.vx_vect,ui_size,C);
		}

		#if (defined __BORLANDC__) && (defined _WIN64 || defined __clang__) // cannot have function "not"
			void _not(cvta X)
		#else
			void not(cvta X)
		#endif
		{
			enforceSize();
			VUB_not(vx_vect,X.vx_vect,ui_size);
		}


/////////////////////////////////////////////////////////////////////////////////////////
//Functions of a sub-set of elements
//


/////////////////////////////////////////////////////////////////////////////////////////
//Mathematical Functions
//


/////////////////////////////////////////////////////////////////////////////////////////
//Optical Density Y = log10( X0 / X )
//


/////////////////////////////////////////////////////////////////////////////////////////
// Graphics
//

            #ifdef __VGRAPH_H
                void xyAutoPlot( cvta X, unsigned form, COLORREF color ) const
                {
                    enforceSize();
                    enforceSize(X.ui_size);
                    VUB_xyAutoPlot( X.vx_vect, vx_vect, ui_size, form, color );
                }

                void xy2AutoPlot( cvta X1, unsigned form1, COLORREF color1,
                         cvta X2, cvta Y2, unsigned form2, COLORREF color2 ) const
                {
                    enforceSize();
                    enforceSize(X1.ui_size);
                    Y2.enforceSize(X2.ui_size);
                    VUB_xy2AutoPlot( X1.vx_vect, vx_vect, ui_size, form1, color1,
                              X2.vx_vect, Y2.vx_vect, X2.ui_size, form2, color2 );
                }

                void yAutoPlot( unsigned form, COLORREF color ) const
                {
                    enforceSize();
                    VUB_yAutoPlot( vx_vect, ui_size, form, color );
                }

                void y2AutoPlot( unsigned form1, COLORREF color1,
                        cvta Y2, unsigned form2, COLORREF color2 ) const
                {
                    enforceSize();
                    Y2.enforceSize();
                    VUB_y2AutoPlot( vx_vect, ui_size, form1, color1,
                             Y2.vx_vect, Y2.ui_size, form2, color2 );
                }

                void xyDataPlot( cvta X, unsigned form, COLORREF color ) const
                {
                    enforceSize();
                    enforceSize(X.ui_size);
                    VUB_xyDataPlot( X.vx_vect, vx_vect, ui_size, form, color );
                }

                void yDataPlot( unsigned form, COLORREF color ) const
                {
                    enforceSize();
                    VUB_yDataPlot( vx_vect, ui_size, form, color );
                }
            #endif   // __VGRAPH_H

/////////////////////////////////////////////////////////////////////////////////////////
// Matrix operations whose result is a vector
//

              //defined by including ubMatObj.h
            void Row_extract(cmta MA, const ui iRow);
            void Col_extract(cmta MA, const ui iCol);
            void Dia_extract(cmta MA);
            void Rows_max(cmta MA);
            void Cols_max(cmta MA);
            void Rows_min(cmta MA);
            void Cols_min(cmta MA);

	};   //  end of class vector<T>


/////////////////////////////////////////////////////////////////////////////////////////
//

	inline void uiVecObj::sortind(cvta X, int dir)
	{
		enforceSize();
		VUB_sortind(vx_vect,X.vx_vect,ui_size,dir);
	}

	inline void uiVecObj::searchV(cvta X, cvta Tab, int mode=0)
	{
		enforceSize();
		Tab.enforceSize();
		VUB_searchV(vx_vect,X.vx_vect,ui_size,Tab.vx_vect,Tab.ui_size,mode);
	}

	inline ui uiVecObj::distribution(cvta Limits, cvta X, int mode=0)
	{
		enforceSize();
		X.enforceSize();
		return VUB_distribution(vx_vect,Limits.vx_vect,ui_size,X.vx_vect,X.ui_size,mode);
	}

	inline ui uiVecObj::cmp_eq0ind(cvta X)
	{
		enforceSize();
		return VUB_cmp_eq0ind(vx_vect,X.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_ne0ind(cvta X)
	{
		enforceSize();
		return VUB_cmp_ne0ind(vx_vect,X.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_gt0ind(cvta X)
	{
		enforceSize();
		return VUB_cmp_gt0ind(vx_vect,X.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_eqCind(cvta X, cta C)
	{
		enforceSize();
		return VUB_cmp_eqCind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_neCind(cvta X, cta C)
	{
		enforceSize();
		return VUB_cmp_neCind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_leCind(cvta X, cta C)
	{
		enforceSize();
		return VUB_cmp_leCind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_ltCind(cvta X, cta C)
	{
		enforceSize();
		return VUB_cmp_ltCind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_geCind(cvta X, cta C)
	{
		enforceSize();
		return VUB_cmp_geCind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_gtCind(cvta X, cta C)
	{
		enforceSize();
		return VUB_cmp_gtCind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_eqVind(cvta X, cvta Y)
	{
		enforceSize();
		return VUB_cmp_eqVind(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_neVind(cvta X, cvta Y)
	{
		enforceSize();
		return VUB_cmp_neVind(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_leVind(cvta X, cvta Y)
	{
		enforceSize();
		return VUB_cmp_leVind(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_ltVind(cvta X, cvta Y)
	{
		enforceSize();
		return VUB_cmp_ltVind(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_geVind(cvta X, cvta Y)
	{
		enforceSize();
		return VUB_cmp_geVind(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_gtVind(cvta X, cvta Y)
	{
		enforceSize();
		return VUB_cmp_gtVind(vx_vect,X.vx_vect,Y.vx_vect,ui_size);
	}

	inline ui uiVecObj::cmp_exclrange0Cind(cvta X, cta C)
	{
		enforceSize();
		return VUB_cmp_exclrange0Cind(vx_vect,X.vx_vect,ui_size,C);
	}

	inline ui uiVecObj::cmp_inclrangeCCind(cvta X, cta CLo, cta CHi)
	{
		enforceSize();
		return VUB_cmp_inclrangeCCind(vx_vect,X.vx_vect,ui_size,CLo,CHi);
	}

	inline ui uiVecObj::cmp_exclrangeCCind(cvta X, cta CLo, cta CHi)
	{
		enforceSize();
		return VUB_cmp_exclrangeCCind(vx_vect,X.vx_vect,ui_size,CLo,CHi);
	}


#ifdef USVECOBJ_H
	inline void usVecObj::UBtoUS(const ubVecObj& X)
	{
		enforceSize();
		V_UBtoUS(vx_vect,X.vx_vect,ui_size);
	}

	inline void ubVecObj::UStoUB(const usVecObj& X)
	{
		enforceSize();
		V_UStoUB(vx_vect,X.vx_vect,ui_size);
	}

	inline void usVecObj::accVUB(const ubVecObj& X)
	{
		enforceSize();
		VUS_accVUB(vx_vect,X.vx_vect,ui_size);
	}
#endif //USVECOBJ

#ifdef UVECOBJ_H
	inline void ubVecObj::UtoUB(const uVecObj& X)
	{
		enforceSize();
		V_UtoUB(vx_vect,X.vx_vect,ui_size);
	}

	inline void uVecObj::UBtoU(const ubVecObj& X)
	{
		enforceSize();
		V_UBtoU(vx_vect,X.vx_vect,ui_size);
	}

	inline void uVecObj::accVUB(const ubVecObj& X)
	{
		enforceSize();
		VU_accVUB(vx_vect,X.vx_vect,ui_size);
	}
#endif //UVECOBJ_H

#ifdef ULVECOBJ_H
	inline void ubVecObj::ULtoUB(const ulVecObj& X)
	{
		enforceSize();
		V_ULtoUB(vx_vect,X.vx_vect,ui_size);
	}

	inline void ulVecObj::UBtoUL(const ubVecObj& X)
	{
		enforceSize();
		V_UBtoUL(vx_vect,X.vx_vect,ui_size);
	}

	inline void ulVecObj::accVUB(const ubVecObj& X)
	{
		enforceSize();
		VUL_accVUB(vx_vect,X.vx_vect,ui_size);
	}
#endif //ULVECOBJ_H

#ifdef UQVECOBJ_H
	inline void uqVecObj::UBtoUQ(const ubVecObj& X)
	{
		enforceSize();
		V_UBtoUQ(vx_vect,X.vx_vect,ui_size);
	}

	inline void ubVecObj::UQtoUB(const uqVecObj& X)
	{
		enforceSize();
		V_UQtoUB(vx_vect,X.vx_vect,ui_size);
	}

	inline void uqVecObj::accVUB(const ubVecObj& X)
	{
		enforceSize();
		VUQ_accVUB(vx_vect,X.vx_vect,ui_size);
	}
#endif //UQVECOBJ_H

#ifdef BIVECOBJ_H
	inline void ubVecObj::BItoUB(const biVecObj& X)
	{
		enforceSize();
		V_BItoUB(vx_vect,X.vx_vect,ui_size);
	}

	inline void biVecObj::UBtoBI(const ubVecObj& X)
	{
		enforceSize();
		V_UBtoBI(vx_vect,X.vx_vect,ui_size);
	}
#endif //BIVECOBJ_H

#ifdef QIVECOBJ_H
	inline void qiVecObj::accVUB(const ubVecObj& X)
	{
		enforceSize();
		VQI_accVUB(vx_vect,X.vx_vect,ui_size);
	}
#endif //QIVECOBJ_H

#ifdef FVECOBJ_H
	inline void fVecObj::accVUB(const ubVecObj& X)
	{
		enforceSize();
		VF_accVUB(vx_vect,X.vx_vect,ui_size);
	}

	inline void fVecObj::addVUB( const fVecObj& X, const ubVecObj& Y);
	{
		enforceSize();
		VF_addVUB(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
	}

	inline void fVecObj::subVUB( const fVecObj& X, const ubVecObj& Y);
	{
		enforceSize();
		VF_subVUB(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
	}

	inline void fVecObj::subrVUB( const fVecObj& X, const ubVecObj& Y);
	{
		enforceSize();
		VF_subrVUB(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
	}

	inline void fVecObj::mulVUB( const fVecObj& X, const ubVecObj& Y);
	{
		enforceSize();
		VF_mulVUB(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
	}

	inline void fVecObj::divVUB( const fVecObj& X, const ubVecObj& Y);
	{
		enforceSize();
		VF_divVUB(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
	}

	inline void fVecObj::divrVUB( const fVecObj& X, const ubVecObj& Y);
	{
		enforceSize();
		VF_divrVUB(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
	}

	inline void fVecObj::UBtoF(const ubVecObj& X)
	{
		enforceSize();
		V_UBtoF(vx_vect,X.vx_vect,ui_size);
	}

	inline int ubVecObj::roundtoUB(const fVecObj& X)
	{
		enforceSize();
		return VF_roundtoUB(vx_vect,X.vx_vect,ui_size);
	}

	inline int ubVecObj::floortoUB(const fVecObj& X)
	{
		enforceSize();
		return VF_floortoUB(vx_vect,X.vx_vect,ui_size);
	}

	inline int ubVecObj::ceiltoUB(const fVecObj& X)
	{
		enforceSize();
		return VF_ceiltoUB(vx_vect,X.vx_vect,ui_size);
	}

	inline int ubVecObj::choptoUB(const fVecObj& X)
	{
		enforceSize();
		return VF_choptoUB(vx_vect,X.vx_vect,ui_size);
	}
#endif //FVECOBJ_H

#ifdef DVECOBJ_H
	inline void dVecObj::accVUB(const ubVecObj& X)
	{
		enforceSize();
		VD_accVUB(vx_vect,X.vx_vect,ui_size);
	}

	inline void dVecObj::addVUB( const dVecObj& X, const ubVecObj& Y);
	{
		enforceSize();
		VD_addVUB(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
	}

	inline void dVecObj::subVUB( const dVecObj& X, const ubVecObj& Y);
	{
		enforceSize();
		VD_subVUB(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
	}

	inline void dVecObj::subrVUB( const dVecObj& X, const ubVecObj& Y);
	{
		enforceSize();
		VD_subrVUB(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
	}

	inline void dVecObj::mulVUB( const dVecObj& X, const ubVecObj& Y);
	{
		enforceSize();
		VD_mulVUB(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
	}

	inline void dVecObj::divVUB( const dVecObj& X, const ubVecObj& Y);
	{
		enforceSize();
		VD_divVUB(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
	}

	inline void dVecObj::divrVUB( const dVecObj& X, const ubVecObj& Y);
	{
		enforceSize();
		VD_divrVUB(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
	}

	inline void dVecObj::UBtoD(const ubVecObj& X)
	{
		enforceSize();
		V_UBtoD(vx_vect,X.vx_vect,ui_size);
	}

	inline int ubVecObj::roundtoUB(const dVecObj& X)
	{
		enforceSize();
		return VD_roundtoUB(vx_vect,X.vx_vect,ui_size);
	}

	inline int ubVecObj::floortoUB(const dVecObj& X)
	{
		enforceSize();
		return VD_floortoUB(vx_vect,X.vx_vect,ui_size);
	}

	inline int ubVecObj::ceiltoUB(const dVecObj& X)
	{
		enforceSize();
		return VD_ceiltoUB(vx_vect,X.vx_vect,ui_size);
	}

	inline int ubVecObj::choptoUB(const dVecObj& X)
	{
		enforceSize();
		return VD_choptoUB(vx_vect,X.vx_vect,ui_size);
	}
#endif //DVECOBJ_H

#ifdef EVECOBJ_H
#if (defined __BORLANDC__) && !(defined _WIN64) //80-bit numbers supported
	inline void eVecObj::accVUB(const ubVecObj& X)
	{
		enforceSize();
		VE_accVUB(vx_vect,X.vx_vect,ui_size);
	}

	inline void eVecObj::addVUB( const eVecObj& X, const ubVecObj& Y);
	{
		enforceSize();
		VE_addVUB(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
	}

	inline void eVecObj::subVUB( const eVecObj& X, const ubVecObj& Y);
	{
		enforceSize();
		VE_subVUB(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
	}

	inline void eVecObj::subrVUB( const eVecObj& X, const ubVecObj& Y);
	{
		enforceSize();
		VE_subrVUB(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
	}

	inline void eVecObj::mulVUB( const eVecObj& X, const ubVecObj& Y);
	{
		enforceSize();
		VE_mulVUB(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
	}

	inline void eVecObj::divVUB( const eVecObj& X, const ubVecObj& Y);
	{
		enforceSize();
		VE_divVUB(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
	}

	inline void eVecObj::divrVUB( const eVecObj& X, const ubVecObj& Y);
	{
		enforceSize();
		VE_divrVUB(vx_vect, X.vx_vect, Y.vx_vect, ui_size);
	}

	inline void eVecObj::UBtoE(const ubVecObj& X)
	{
		enforceSize();
		V_UBtoE(vx_vect,X.vx_vect,ui_size);
	}

	inline int ubVecObj::roundtoUB(const eVecObj& X)
	{
		enforceSize();
		return VE_roundtoUB(vx_vect,X.vx_vect,ui_size);
	}

	inline int ubVecObj::floortoUB(const eVecObj& X)
	{
		enforceSize();
		return VE_floortoUB(vx_vect,X.vx_vect,ui_size);
	}

	inline int ubVecObj::ceiltoUB(const eVecObj& X)
	{
		enforceSize();
		return VE_ceiltoUB(vx_vect,X.vx_vect,ui_size);
	}

	inline int ubVecObj::choptoUB(const eVecObj& X)
	{
		enforceSize();
		return VE_choptoUB(vx_vect,X.vx_vect,ui_size);
	}
#endif //__BORLANDC__
#endif //EVECOBJ_H

#ifdef CFVECOBJ_H
#endif //CFVECOBJ_H

#ifdef CDVECOBJ_H
#endif //CDVECOBJ_H

#ifdef CEVECOBJ_H
#if (defined __BORLANDC__) && !(defined _WIN64) //80-bit numbers supported
#endif //__BORLANDC__
#endif //CEVECOBJ_H

#if defined _MSC_VER || (defined __BORLANDC__ && __BORLANDC__ >= 0x500)
}  // end of namespace OptiVec
#endif

#undef cvta
#undef cmta
#undef cuia
#undef cta

#undef vta
#undef uia
#undef ta

#undef vt
#undef t
#undef tVector

#undef vtcplx
#undef tcplx

#undef tVecObj
#ifdef __BORLANDC__
#pragma warn .inl
#endif

#define UBVECOBJ_H
#endif //UBVECOBJ_H
