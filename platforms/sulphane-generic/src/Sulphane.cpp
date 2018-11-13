/** 
 * This file is part of project URSA. More information on the project
 * can be found at 
 *
 * URSA's repository at GitHub: http://https://github.com/andersondomingues/ursa
 *
 * Copyright (C) 2018 Anderson Domingues, <ti.andersondomingues@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA. **/
#include <iostream>
#include <iomanip>

//simulation API
#include <Event.h>
#include <Simulator.h>

//model API
#include <UMemory.h>
#include <THellfireProcessor.h>
#include <TRouter.h>
#include <TNetif.h> 

#include <ProcessingElement.h>

#define CYCLES_TO_SIM 10000000
#define NOC_H_SIZE 3
#define NOC_W_SIZE 3

//instantiates a mesh of MxN PE
ProcessingElement* pes[NOC_W_SIZE][NOC_H_SIZE];
Metric* metrics[NOC_W_SIZE][NOC_H_SIZE];

void connect_routers(TRouter* r1, uint32_t p1, TRouter* r2, uint32_t p2){
	r1->SetOutputBuffer(r2->GetInputBuffer(p2), p1);
	r2->SetOutputBuffer(r1->GetInputBuffer(p1), p2);
}

int main(int argc, char** argv){

    argc = argc; //workaround to use -Wextra

	std::cout << "Sulphane: (H2S) Hermes-Hellfire SoC (Width=" << NOC_W_SIZE << ", Height=" << NOC_H_SIZE << ")" << std::endl;
	std::cout << "Simulation step set to " << CYCLES_TO_SIM << " cycles." << std::endl;
	
	//populate PEs
	for(int x = 0; x < NOC_W_SIZE; x++)
		for(int y = 0; y < NOC_H_SIZE; y++)
			pes[x][y] = new ProcessingElement(x, y);

	//connect PE to each other (left-to-right, right-to-left connections)	
	for(int x = 0; x < NOC_W_SIZE - 1; x++)
		for(int y = 0; y < NOC_H_SIZE; y++)
			connect_routers(pes[x][y]->GetRouter(), EAST, pes[x+1][y]->GetRouter(), WEST);
			
	//connect PE to each other (bottom-to-top, top-to-bottom connections)
	for(int x = 0; x < NOC_W_SIZE; x++)
		for(int y = 0; y < NOC_H_SIZE - 1; y++)
			connect_routers(pes[x][y]->GetRouter(), NORTH, pes[x][y+1]->GetRouter(), SOUTH);
	
	//instantiate simulation
	Simulator* s = new Simulator();
		
	//schedule hardware to be simulated
	for(int x = 0; x < NOC_W_SIZE; x++){
		for(int y = 0; y < NOC_H_SIZE; y++){
			
			s->Schedule(Event(1, pes[x][y]->GetCpu()));
			s->Schedule(Event(1, pes[x][y]->GetRouter()));
			s->Schedule(Event(1, pes[x][y]->GetNetif()));
			
			std::cout << pes[x][y]->ToString() << std::endl;		
		}
	}

	//load binaries into main memories
	int index = 0;
	std::string code_file;
	for(int x = 0; x < NOC_W_SIZE; x++){
		for(int y = 0; y < NOC_H_SIZE; y++){
				index = x + NOC_W_SIZE * y;
				code_file = std::string(argv[1]) + "code" + std::to_string(index) + ".bin";
				pes[x][y]->GetMem0()->LoadBin(code_file, MEM0_BASE, MEM0_SIZE);
		}
	}
	
	//keep simulating until something happen
	try{
		//while(1){
		s->Run(CYCLES_TO_SIM);
		//	std::cout << "Simulation: " << CYCLES_TO_SIM << " cycles has been passed since last message." << std::endl;
		//}
	}catch(std::runtime_error& e){
		std::cout << e.what() << std::endl;
	}
	
	//show simulation statistics
	std::cout << "========== CPU ENERGY STATISTICS =========" << std::endl;
	for(int i = 0; i < NOC_W_SIZE; i++){
		for(int j = 0; j < NOC_H_SIZE; j++){
			
			Metric* energy = pes[i][j]->GetCpu()->GetMetric(Metrics::ENERGY);
			
			std::cout << pes[i][j]->GetCpu()->GetName() << ":"
			          << "\tsamples=" << std::dec << energy->GetSamples() 
					  << "\taccumulative=" << setprecision(10) << energy->GetAccumulative() << "pJ"
					  << "\tmean=" << (energy->GetAccumulative() / energy->GetSamples()) << "pJ"<< std::endl;
		}
		
	}
}
