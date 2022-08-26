#include "Position.h"
#include <cmath>
#include <assert.h>

bool is_close(double a, double b, double epsilon = 1e-11) {
  return std::fabs(a - b) < epsilon;
}

void test_posizione() {
  Posizione p{3., 4., 5.};

  assert( is_close( p.getX(), 3.0 ) );
  assert( is_close( p.getY(), 4.0 ) );
  assert( is_close( p.getZ(), 5.0 ) );

  assert( is_close( p.getTheta(), 0.78539816339745 ) );
  assert( is_close( p.getPhi(), 0.92729521800161 ) );
  assert( is_close( p.getR(), 7.0710678118655 ) );

  assert( is_close( p.getRho(), 5.0 ) );

  Posizione p2{6.0, 5.0, -3.0};
  assert( is_close( p.Distanza(p2), 8.602325267042627 ) );
}

//Costruttore di default
Posizione::Posizione(){
	m_x=0;
	m_y=0;
	m_z=0;
}
Posizione::Posizione(double x, double y, double z){
	m_x=x;
	m_y=y;
	m_z=z;
}
Posizione::Posizione(double rho, double theta){
	m_rho=rho;
	m_theta=theta;
    m_x = m_rho * cos(m_theta);
    m_y = m_rho * sin(m_theta);
    m_z = 0;
}
//Distruttore
Posizione::~Posizione(){
}

//Coordinate cartesiane
double Posizione::getX() const {
	return m_x;
}
double Posizione::getY() const {
	return m_y;
}
double Posizione::getZ() const {
	return m_z;
}
//========================================
void Posizione::SetX(double x){
    m_x = x;
}
void Posizione::SetY(double y){
    m_y = y;
}
void Posizione::SetZ(double z){
    m_z = z;
}
//========================================

//Coordinate sferiche
double Posizione::getR() const {
	return sqrt( m_x*m_x + m_y*m_y + m_z*m_z );
}
double Posizione::getPhi() const {
	return atan2( m_y , m_x );
}
double Posizione::getTheta() const {
	return acos( m_z / getR() );
}

//Coordinate cilindriche (raggio)
double Posizione::getRho() const {
	return sqrt( m_x*m_x + m_y*m_y );
}

//Distanza da un altro punto
double Posizione::Distanza( const Posizione& b) const {
	return sqrt( pow( getX()-b.getX(), 2 )
				+pow( getY()-b.getY(), 2 )
				+pow( getZ()-b.getZ(), 2 ) );
}


