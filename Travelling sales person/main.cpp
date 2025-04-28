#include "Include//ACO.hpp"
#include "Include//PSOForTaxi.hpp"
#include <vector>

int main() {
    std::vector<place> places = {
            {"Flaa", 60.432045, 9.476896},
            {"Oslo", 59.907894, 10.753953},
            {"Humla", 62.445129, 6.296201},
            {"Sauda", 59.652350, 6.360653},
            {"Nordkapp", 71.167349, 25.780048},
            {"Roeros", 62.576018, 11.386869},
            {"Lindesnes", 57.982666, 7.047108},
            {"Trondheim", 63.414641, 10.398322},
            {"Svinesundbroa", 59.094726, 11.251470},
            {"Galdhoepiggen", 61.635301, 8.311582},
            {"Grunge", 59.722411, 7.699088},
            {"Sandefjord", 59.148040, 10.27577},
            {"Narvik", 68.431298, 17.435380},
            {"Kautokeino", 69.013768, 23.049282},
            {"Bergen", 60.391263, 5.322054},
            {"Stavanger", 58.969976, 5.733107},
            {"Tromsoe", 69.649595, 18.956343},
            {"Bodoe", 67.282902, 14.371069},
            {"Kristiansand", 58.146457, 7.995970},
            {"Haugesund", 59.413938, 5.267544},
            {"Aalesund", 62.472228, 6.149482},
            {"Molde", 62.737052, 7.159121},
            {"Hamar", 60.794533, 11.067998},
            {"Lillehammer", 61.115271, 10.466231},
            {"Harstad", 68.798550, 16.541553},
            {"Alta", 69.968872, 23.271643},
            {"Kirkenes", 69.725181, 30.045832},
            {"Svolvaer", 68.234079, 14.564118},
            {"Leknes", 68.147238, 13.612711},
            {"Sortland", 68.695510, 15.414877},
            {"Mo i Rana", 66.312780, 14.142820},
            {"Mosjoeen", 65.836203, 13.190072},
            {"Namsos", 64.464580, 11.495919},
            {"Steinkjer", 64.014869, 11.495937},
            {"Levanger", 63.746153, 11.295329},
            {"Verdal", 63.792586, 11.481431},
            {"Oppdal", 62.594008, 9.691877},
            {"Dombaas", 62.074874, 9.125682},
            {"Otta", 61.771982, 9.536311},
            {"Fagernes", 60.985393, 9.232637},
            {"Gol", 60.699223, 8.957711},
            {"Geilo", 60.533294, 8.205558},
            {"Eidfjord", 60.471543, 7.068034},
            {"Odda", 60.068473, 6.543013},
            {"Voss", 60.628026, 6.418407},
            {"Foerde", 61.452858, 5.851948},
            {"Floroe", 61.599841, 5.032773},
            {"Stryn", 61.904078, 6.718393},
            {"Sandane", 61.776400, 6.217122},
            {"Sogndal", 61.229752, 7.103330},
            {"Volda", 62.146529, 6.078021},
            {"Sunndalsoera", 62.673618, 8.564037},
            {"Kongsvinger", 60.190189, 11.997293},
            {"Halden", 59.129912, 11.384982},
            {"Fredrikstad", 59.220540, 10.933144},
            {"Sarpsborg", 59.283832, 11.108237},
            {"Drammen", 59.743530, 10.204488},
            {"Hoenefoss", 60.169246, 10.256863},
            {"Toensberg", 59.267626, 10.407520},
            {"Arendal", 58.461436, 8.772200},
            {"Grimstad", 58.342256, 8.594308},
            {"Mandal", 58.027556, 7.453442},
            {"Egersund", 58.451396, 5.999206}
    };

    std::vector<place> taxiLocationsRiga = {
            {"SIA", 56.993659, 24.123796},
            {"RedCab", 56.968273, 24.114356},
            {"TAKSI", 56.949601, 24.105179},
            {"Forus", 56.940996, 24.122590},
            {"Bolt", 56.935426, 24.103262},
            {"Avoiss", 56.928342, 24.101790},
            {"Riga taxi", 56.909143, 24.081797},
            {"Alviksa", 56.888130, 24.231152},
            {"Smile", 56.923775, 24.166296},
            {"SOS", 56.939074, 24.205089},
            {"Baltic taxi", 56.963289, 24.149563},
            {"24/7 taxi", 56.934568, 24.043708},
            {"Riga Airport Transfers", 56.919618, 23.992172},
            {"Baltic Taxi Zona", 56.923507, 23.989721}
    };

    float greaterRigaLonMin = 23.957933;
    float greaterRigaLonMax = 24.402939;
    float greaterRigaLatMin = 56.821040;
    float greaterRigaLatMax = 57.001724;

    //For the ACO to work the line below, number 96, and aco.moveAnts(), line 101 have to be commented in. It would also be
    //an advantage to comment out line 97, 98 and 102 which is the PSO code.
    //ACO aco(places, 10, 10000, 0.5, 0.5, 0.01, 1.0, 4.0);
    PSOForTaxi taxiProblem(greaterRigaLatMin, greaterRigaLatMax, greaterRigaLonMin, greaterRigaLonMax, taxiLocationsRiga, 100,
                           1000, 0.4, 1.2, 2.5);

    while (true){
        //aco.moveAnts();
        taxiProblem.calculatePSO();
    }

    return 0;
}
