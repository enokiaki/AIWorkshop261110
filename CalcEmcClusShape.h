#ifndef CALCEMCCLUSSHAPE_H
#define CALCEMCCLUSSHAPE_H

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
		      );

#endif
