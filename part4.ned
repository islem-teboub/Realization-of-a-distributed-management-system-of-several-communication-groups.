
package part4;

simple Noeud
{
    @display("i=device/wifilaptop");
    gates:
        input inport[];
        output outport[];
}
network Part4
{
    parameters:
        int x;

        int i = 0;
        int j = 0;

        @display("bgb=369,341");
    submodules:

        noeud[x]: Noeud;
    connections:

        for i=0..x-1, for j=0..x-1, if (i != j) {
            noeud[i].outport++ --> {  delay = 500 ms; } --> noeud[j].inport++;
            noeud[i].inport++ <-- {  delay = 500 ms; } <-- noeud[j].outport++;
        }
}


