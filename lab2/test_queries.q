//This file was generated from UPPAAL 4.0.6 (rev. 2987), March 2007

/*

*/
A[] not(P1.local_light_on == 1 and P3.local_light_on == 1)

/*

*/
E<> (NS_car == 0 and SN_car==0 and WE_car == 0 and EW_car == 0)

/*

*/
E<>  (P3.local_light_on == 1 and P4.local_light_on == 0)

/*

*/
E<>  (P1.local_light_on == 1 and P2.local_light_on == 0)

/*

*/
E<>  (P3.local_light_on == 1 and P4.local_light_on == 1)

/*

*/
E<>  (P1.local_light_on == 1 and P2.local_light_on == 1)
