#ifndef _Experimental_1D_GaussianQuadratures_GaussLegendreQuadrature_hpp
#define _Experimental_1D_GaussianQuadratures_GaussLegendreQuadratrue_hpp

/** @file GaussLegendre.hpp
  * @brief 
  * @author C.D. Clark III
  * @date 08/04/17
  */

#include<array>

namespace Experimental {
namespace _1D {
namespace GQ {

namespace detail {
template<typename T, size_t Order>
class GaussLegendreQuadrature_imp
{
  protected:
    // should we store weights and abscissas in an inter-leaved array?
    std::array<T,Order> w;
    std::array<T,Order> x;

  public:
    GaussLegendreQuadrature_imp() {};
    virtual ~GaussLegendreQuadrature_imp() {};

    template<typename F, typename X>
    T operator()( F f, X a, X b ) const;

    // A reverse communication version
    template<typename X>
    struct State {
      size_t i;
      X x;
      X a, b;
      X apb;
      X amb;
      T f;
      T sum;

      bool initialized = false;
    };

    template<typename X>
    T operator()( X a, X b, State<X>& state) const;

    const std::array<T,Order>& getX() const {return x;}
    const std::array<T,Order>& getW() const {return w;}

};


template<typename T, size_t Order>
template<typename F, typename X>
T GaussLegendreQuadrature_imp<T,Order>::operator()(F f, X a, X b) const
{
  X apb = (b + a)/2;
  X amb = (b - a)/2;

  T sum = 0;
  for(int i = 0; i < Order; i++)
    sum += w[i]*f( apb + amb*x[i] );
  sum *= amb;

  return sum;
}

template<typename T, size_t Order>
template<typename X>
T GaussLegendreQuadrature_imp<T,Order>::operator()(X a, X b, State<X>& state) const
{
  if( !state.initialized )
  {
    state.i = 0;
    state.a = a;
    state.b = b;
    state.apb = (b + a)/2;
    state.amb = (b - a)/2;
    state.sum = 0;
    state.initialized = true;
  }
  else
  {
    state.sum += w[state.i]*state.f;
    state.i++;
  }

  if( state.i >= Order )
  {
    state.sum *= state.amb;
    return false;
  }

  state.x = state.apb + state.amb*x[state.i];

  return true;
}

}


/** @class GaussLegendreQuadrature
  * @brief 
  * @author C.D. Clark III
  */
template<typename T, size_t Order>
class GaussLegendreQuadrature 
{
};

template<typename T>
class GaussLegendreQuadrature<T,8> : public detail::GaussLegendreQuadrature_imp<T,8>
{

  protected:
    using detail::GaussLegendreQuadrature_imp<T,8>::w;
    using detail::GaussLegendreQuadrature_imp<T,8>::x;
  public:
    GaussLegendreQuadrature()
    {
      // these weights and abscissa were taken from https://pomax.github.io/bezierinfo/legendre-gauss.html#n8
      w[0 ] =  0.3626837833783620; x[0 ] =  -0.1834346424956498;
      w[1 ] =  0.3626837833783620; x[1 ] =   0.1834346424956498;
      w[2 ] =  0.3137066458778873; x[2 ] =  -0.5255324099163290;
      w[3 ] =  0.3137066458778873; x[3 ] =   0.5255324099163290;
      w[4 ] =  0.2223810344533745; x[4 ] =  -0.7966664774136267;
      w[5 ] =  0.2223810344533745; x[5 ] =   0.7966664774136267;
      w[6 ] =  0.1012285362903763; x[6 ] =  -0.9602898564975363;
      w[7 ] =  0.1012285362903763; x[7 ] =   0.9602898564975363;
    }
    virtual ~GaussLegendreQuadrature() {};

};

template<typename T>
class GaussLegendreQuadrature<T,16> : public detail::GaussLegendreQuadrature_imp<T,16>
{

  protected:
    using detail::GaussLegendreQuadrature_imp<T,16>::w;
    using detail::GaussLegendreQuadrature_imp<T,16>::x;
  public:
    GaussLegendreQuadrature()
    {
      // these weights and abscissa were taken from https://pomax.github.io/bezierinfo/legendre-gauss.html#n64
      w[0 ] =  0.1894506104550685; x[0 ] =  -0.0950125098376374;
      w[1 ] =  0.1894506104550685; x[1 ] =   0.0950125098376374;
      w[2 ] =  0.1826034150449236; x[2 ] =  -0.2816035507792589;
      w[3 ] =  0.1826034150449236; x[3 ] =   0.2816035507792589;
      w[4 ] =  0.1691565193950025; x[4 ] =  -0.4580167776572274;
      w[5 ] =  0.1691565193950025; x[5 ] =   0.4580167776572274;
      w[6 ] =  0.1495959888165767; x[6 ] =  -0.6178762444026438;
      w[7 ] =  0.1495959888165767; x[7 ] =   0.6178762444026438;
      w[8 ] =  0.1246289712555339; x[8 ] =  -0.7554044083550030;
      w[9 ] =  0.1246289712555339; x[9 ] =   0.7554044083550030;
      w[10] =  0.0951585116824928; x[10] =  -0.8656312023878318;
      w[11] =  0.0951585116824928; x[11] =   0.8656312023878318;
      w[12] =  0.0622535239386479; x[12] =  -0.9445750230732326;
      w[13] =  0.0622535239386479; x[13] =   0.9445750230732326;
      w[14] =  0.0271524594117541; x[14] =  -0.9894009349916499;
      w[15] =  0.0271524594117541; x[15] =   0.9894009349916499;
    }
    virtual ~GaussLegendreQuadrature() {};

};

template<typename T>
class GaussLegendreQuadrature<T,32> : public detail::GaussLegendreQuadrature_imp<T,32>
{

  protected:
    using detail::GaussLegendreQuadrature_imp<T,32>::w;
    using detail::GaussLegendreQuadrature_imp<T,32>::x;
  public:
    GaussLegendreQuadrature()
    {
      // these weights and abscissa were taken from https://pomax.github.io/bezierinfo/legendre-gauss.html#n64
      w[0 ] =  0.0965400885147278; x[0 ] =  -0.0483076656877383;
      w[1 ] =  0.0965400885147278; x[1 ] =   0.0483076656877383;
      w[2 ] =  0.0956387200792749; x[2 ] =  -0.1444719615827965;
      w[3 ] =  0.0956387200792749; x[3 ] =   0.1444719615827965;
      w[4 ] =  0.0938443990808046; x[4 ] =  -0.2392873622521371;
      w[5 ] =  0.0938443990808046; x[5 ] =   0.2392873622521371;
      w[6 ] =  0.0911738786957639; x[6 ] =  -0.3318686022821277;
      w[7 ] =  0.0911738786957639; x[7 ] =   0.3318686022821277;
      w[8 ] =  0.0876520930044038; x[8 ] =  -0.4213512761306353;
      w[9 ] =  0.0876520930044038; x[9 ] =   0.4213512761306353;
      w[10] =  0.0833119242269467; x[10] =  -0.5068999089322294;
      w[11] =  0.0833119242269467; x[11] =   0.5068999089322294;
      w[12] =  0.0781938957870703; x[12] =  -0.5877157572407623;
      w[13] =  0.0781938957870703; x[13] =   0.5877157572407623;
      w[14] =  0.0723457941088485; x[14] =  -0.6630442669302152;
      w[15] =  0.0723457941088485; x[15] =   0.6630442669302152;
      w[16] =  0.0658222227763618; x[16] =  -0.7321821187402897;
      w[17] =  0.0658222227763618; x[17] =   0.7321821187402897;
      w[18] =  0.0586840934785355; x[18] =  -0.7944837959679424;
      w[19] =  0.0586840934785355; x[19] =   0.7944837959679424;
      w[20] =  0.0509980592623762; x[20] =  -0.8493676137325700;
      w[21] =  0.0509980592623762; x[21] =   0.8493676137325700;
      w[22] =  0.0428358980222267; x[22] =  -0.8963211557660521;
      w[23] =  0.0428358980222267; x[23] =   0.8963211557660521;
      w[24] =  0.0342738629130214; x[24] =  -0.9349060759377397;
      w[25] =  0.0342738629130214; x[25] =   0.9349060759377397;
      w[26] =  0.0253920653092621; x[26] =  -0.9647622555875064;
      w[27] =  0.0253920653092621; x[27] =   0.9647622555875064;
      w[28] =  0.0162743947309057; x[28] =  -0.9856115115452684;
      w[29] =  0.0162743947309057; x[29] =   0.9856115115452684;
      w[30] =  0.0070186100094701; x[30] =  -0.9972638618494816;
      w[31] =  0.0070186100094701; x[31] =   0.9972638618494816;
    }
    virtual ~GaussLegendreQuadrature() {};

};

template<typename T>
class GaussLegendreQuadrature<T,64> : public detail::GaussLegendreQuadrature_imp<T,64>
{

  protected:
    using detail::GaussLegendreQuadrature_imp<T,64>::w;
    using detail::GaussLegendreQuadrature_imp<T,64>::x;
  public:
    GaussLegendreQuadrature()
    {
      // these weights and abscissa were taken from https://pomax.github.io/bezierinfo/legendre-gauss.html#n64
      w[0 ] =  0.0486909570091397; x[0 ] =  -0.0243502926634244;
      w[1 ] =  0.0486909570091397; x[1 ] =   0.0243502926634244;
      w[2 ] =  0.0485754674415034; x[2 ] =  -0.0729931217877990;
      w[3 ] =  0.0485754674415034; x[3 ] =   0.0729931217877990;
      w[4 ] =  0.0483447622348030; x[4 ] =  -0.1214628192961206;
      w[5 ] =  0.0483447622348030; x[5 ] =   0.1214628192961206;
      w[6 ] =  0.0479993885964583; x[6 ] =  -0.1696444204239928;
      w[7 ] =  0.0479993885964583; x[7 ] =   0.1696444204239928;
      w[8 ] =  0.0475401657148303; x[8 ] =  -0.2174236437400071;
      w[9 ] =  0.0475401657148303; x[9 ] =   0.2174236437400071;
      w[10] =  0.0469681828162100; x[10] =  -0.2646871622087674;
      w[11] =  0.0469681828162100; x[11] =   0.2646871622087674;
      w[12] =  0.0462847965813144; x[12] =  -0.3113228719902110;
      w[13] =  0.0462847965813144; x[13] =   0.3113228719902110;
      w[14] =  0.0454916279274181; x[14] =  -0.3572201583376681;
      w[15] =  0.0454916279274181; x[15] =   0.3572201583376681;
      w[16] =  0.0445905581637566; x[16] =  -0.4022701579639916;
      w[17] =  0.0445905581637566; x[17] =   0.4022701579639916;
      w[18] =  0.0435837245293235; x[18] =  -0.4463660172534641;
      w[19] =  0.0435837245293235; x[19] =   0.4463660172534641;
      w[20] =  0.0424735151236536; x[20] =  -0.4894031457070530;
      w[21] =  0.0424735151236536; x[21] =   0.4894031457070530;
      w[22] =  0.0412625632426235; x[22] =  -0.5312794640198946;
      w[23] =  0.0412625632426235; x[23] =   0.5312794640198946;
      w[24] =  0.0399537411327203; x[24] =  -0.5718956462026340;
      w[25] =  0.0399537411327203; x[25] =   0.5718956462026340;
      w[26] =  0.0385501531786156; x[26] =  -0.6111553551723933;
      w[27] =  0.0385501531786156; x[27] =   0.6111553551723933;
      w[28] =  0.0370551285402400; x[28] =  -0.6489654712546573;
      w[29] =  0.0370551285402400; x[29] =   0.6489654712546573;
      w[30] =  0.0354722132568824; x[30] =  -0.6852363130542333;
      w[31] =  0.0354722132568824; x[31] =   0.6852363130542333;
      w[32] =  0.0338051618371416; x[32] =  -0.7198818501716109;
      w[33] =  0.0338051618371416; x[33] =   0.7198818501716109;
      w[34] =  0.0320579283548516; x[34] =  -0.7528199072605319;
      w[35] =  0.0320579283548516; x[35] =   0.7528199072605319;
      w[36] =  0.0302346570724025; x[36] =  -0.7839723589433414;
      w[37] =  0.0302346570724025; x[37] =   0.7839723589433414;
      w[38] =  0.0283396726142595; x[38] =  -0.8132653151227975;
      w[39] =  0.0283396726142595; x[39] =   0.8132653151227975;
      w[40] =  0.0263774697150547; x[40] =  -0.8406292962525803;
      w[41] =  0.0263774697150547; x[41] =   0.8406292962525803;
      w[42] =  0.0243527025687109; x[42] =  -0.8659993981540928;
      w[43] =  0.0243527025687109; x[43] =   0.8659993981540928;
      w[44] =  0.0222701738083833; x[44] =  -0.8893154459951141;
      w[45] =  0.0222701738083833; x[45] =   0.8893154459951141;
      w[46] =  0.0201348231535302; x[46] =  -0.9105221370785028;
      w[47] =  0.0201348231535302; x[47] =   0.9105221370785028;
      w[48] =  0.0179517157756973; x[48] =  -0.9295691721319396;
      w[49] =  0.0179517157756973; x[49] =   0.9295691721319396;
      w[50] =  0.0157260304760247; x[50] =  -0.9464113748584028;
      w[51] =  0.0157260304760247; x[51] =   0.9464113748584028;
      w[52] =  0.0134630478967186; x[52] =  -0.9610087996520538;
      w[53] =  0.0134630478967186; x[53] =   0.9610087996520538;
      w[54] =  0.0111681394601311; x[54] =  -0.9733268277899110;
      w[55] =  0.0111681394601311; x[55] =   0.9733268277899110;
      w[56] =  0.0088467598263639; x[56] =  -0.9833362538846260;
      w[57] =  0.0088467598263639; x[57] =   0.9833362538846260;
      w[58] =  0.0065044579689784; x[58] =  -0.9910133714767443;
      w[59] =  0.0065044579689784; x[59] =   0.9910133714767443;
      w[60] =  0.0041470332605625; x[60] =  -0.9963401167719553;
      w[61] =  0.0041470332605625; x[61] =   0.9963401167719553;
      w[62] =  0.0017832807216964; x[62] =  -0.9993050417357722;
      w[63] =  0.0017832807216964; x[63] =   0.9993050417357722;
    }
    virtual ~GaussLegendreQuadrature() {};

};


}
}
}

#endif // include protector
