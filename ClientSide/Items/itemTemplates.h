#pragma once
#include<string>
// template for items
struct itemTemplate {
	public:
		std::string name;
		int cost;
		int charges;
		bool consumable;
		std::string imagePath;
		void construct(std::string pname,int pcost,int pcharges,bool pconsumable,std::string pimagePath) {//for child structs
			name = pname;
			cost = pcost;
			charges = pcharges;
			consumable = pconsumable;
			imagePath = pimagePath;
		}
		itemTemplate() {
			name ="";
			cost =0;
			charges =0;
			consumable =false;
			imagePath ="";
		}
		itemTemplate(std::string pname, int pcost, int pcharges, bool pconsumable, std::string pimagePath) {
			construct(pname, pcost, pcharges, pconsumable, pimagePath);
		}
};