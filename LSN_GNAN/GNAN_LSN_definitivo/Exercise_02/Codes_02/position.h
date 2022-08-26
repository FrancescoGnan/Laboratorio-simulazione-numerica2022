#pragma once

class Posizione {

public:
  Posizione();
  Posizione(double x, double y, double z);
  ~Posizione();

  double getX() const;
  double getY() const;
  double getZ() const;
  void SetX(double);
  void SetY(double);
  void SetZ(double);
  double getTheta() const;
  double getPhi() const;
  double getR() const;
  double getRho() const;

  double Distanza(const Posizione &) const;


private:
  double m_x, m_y, m_z;
};