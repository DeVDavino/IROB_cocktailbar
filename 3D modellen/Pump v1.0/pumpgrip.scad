module pumpgrip() {
    difference(){
        union(){
            //translate([0,0,0]) cube([20,30,2.5]);
            //translate([0,0,9.5]) cube([20,35,2.5]);
            //translate([0,-5,0]) cube([20,10,12]); 
            
            //translate([0,-15,0]) cube([20,10,12]);
            rotate([0,90,0]) translate([-12,-25,13]) cube([12,10,4]);
            translate([17,-25,2]) cube([4,3,3]);
            translate([17,-25,7]) cube([4,3,3]);
        }
        
        union(){
            translate([10,25,0]) cylinder(d=16, h=5);
            //rotate([90,0,0]) translate([10,6,-10]) cylinder(d=5, h=30);
        }
    }
}




pumpgrip($fn=100);