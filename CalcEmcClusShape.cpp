#include <vector>    // for vector
#include <algorithm> // for sort
#include "INTT_Calo_Ana.h"
#include "INTT_Calo_trkReco.h"
#include "CalcEmcClusShape.h"

struct Stower {
  float phi;
  float eta;
  float e;

  Stower(float phi_, float eta_, float e_) {
    phi = phi_;
    eta = eta_;
    e   = e_;
  }
  
  bool operator < (const Stower & another) const {
    return phi < another.phi;
  }
};

void CalcEmcClusShape(int iEmc,     // index of Emc cluster
		      int sign,     // sign of the charge strikng the Emc 
		      float phi_e,  // phi of Emc cluster
		      int &ntower,  // # of towers of the Emc cluster
		      float &t_phi_b, // phi of towers before the Cluster center phi-row.
		      float &t_e_b,   // sum of energy of towers with t_phi_b
		      float &t_phi_c, // phi of towers in the Cluster center phi-rows
		      float &t_e_c,    // sum of energy of towers with t_phi_c
		      float &t_phi_a,  // phi of towers after t_phi_b
		      float &t_e_a     // sum of enery of towers with t_phi_a
		      ) {
  vector<float> vtower_e = emc_tower_e->at(iEmc);
  vector<float> vtower_phi = emc_tower_phi->at(iEmc);
  vector<float> vtower_eta = emc_tower_eta->at(iEmc);
  
  ntower = vtower_e.size();
  t_phi_b = -99;
  t_phi_a = -99;
  t_e_b = 0;
  t_e_c = 0;
  t_e_a = 0;

  vector<Stower> vStower;

  for(int itower=0;itower<ntower;itower++) {
    float t_phi = vtower_phi.at(itower);
    float t_eta = vtower_eta.at(itower);
    float t_e   = vtower_e.at(itower);

    vStower.push_back(Stower(t_phi,t_eta,t_e));
  }
  
  sort(vStower.begin(),vStower.end());
  // print after sort
  //  cout << "sign = "<<sign<<" phi_e = "<<phi_e<<endl;
  //  cout << "after sort"<<endl;

  // Find towers in the Cluster center in phi and sum of their energy
  for (int itower=0; itower<ntower; itower++) {
    /*
    cout << itower;
    cout << " phi = "<<(vStower.at(itower)).phi;
    cout << " eta = "<<(vStower.at(itower)).eta;
    cout << " e = "<<(vStower.at(itower)).e <<endl;
    */
    Stower tower = vStower.at(itower);
    float tower_phi = tower.phi;
    if(abs(tower_phi - phi_e)<0.015) {
      t_phi_c = tower_phi;
      t_e_c +=  tower.e;
    }
  }

  // Find towers before the CoG tower from the track striking direction
  for (int itower=0; itower<ntower; itower++) {
    Stower tower = vStower.at(itower);
    if(abs(tower.phi - t_phi_c - sign*0.025)< 0.01) {
      t_phi_b = tower.phi;
      t_e_b += tower.e;
    }
  }

  // Find towers after the CoG tower from the track striking direction
  for (int itower=0; itower<ntower; itower++) {
    Stower tower = vStower.at(itower);
    if(abs(tower.phi - t_phi_c + sign*0.025)< 0.01) {
      t_phi_a = tower.phi;
      t_e_a += tower.e;
    }
  }

  /*
  cout << "t_phi_b = "<<t_phi_b;
  cout << " t_e_b = "<<t_e_b<<endl;
  cout << "t_phi_c = "<<t_phi_c;
  cout << " t_e_c = "<<t_e_c<<endl;
  cout << "t_phi_a = "<<t_phi_a;
  cout << " t_e_a = "<<t_e_a<<endl;
  cout <<endl;
  */
}
