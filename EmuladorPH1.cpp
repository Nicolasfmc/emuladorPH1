#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <bits/stdc++.h>

using namespace std;

string converteHex(int valor){
    stringstream ss;
    ss << hex << valor;
    string res = ss.str();
    return res;
}


int main() {
    int memoria[256]; // vetor memoria
    int programcounter = 0;
    int acumulador = 0;
    int instrucao;
    int rem; // endereco  de memoria
    int rdm; // dados da memoria
    int endr; // endereco do valor
    int value; //valor contido no endr
    int count = 0; // contador de instrucoes executadas

    int comp [256];
    int indice;

    char nome[256]; // nome do arquivo
    string linha;
	FILE *file;

    cout << "Informe o nome do arquivo:" << endl;
	cin >> nome;

    file = fopen(nome, "r"); //abre o arquivo para leitura

    if (file == NULL){ // verifica se o arquivo existes
       cout << "erro ao abrir o arquivo " << endl;
    }

    cout << "Input file: " << nome << endl << endl;

    while(!feof(file)) { // enquanto não for o final do arquivo
        fscanf(file ,"%x %x", &endr, &value); // lê a linha
		memoria[endr] = value; // guarda na memoria o endereço e seu valor
        comp[endr] = value;
        indice = endr;
    }

    fclose(file);

    do {
        // Configurando os registradores
        rem = programcounter; // registrador de enderecos recebe a proxima instrucao
        rdm = memoria[rem]; // registrador de dados recebe o valor que esta na memoria do endereco
        instrucao = rdm;
        switch (instrucao) {
            case 0x00: // instrucao NOP
                programcounter++; //atualiza pc em 1

                cout << "NOP" << endl; // printa a instrucao
                count++; // atualiza contador de instruÃ§Ãµes
                break;
            case 0x10: // LDR
                programcounter += 2; // atualiza pc em 2
                rdm = memoria[rem + 1]; // pega o valor da instrucao

                cout << "LDR " << converteHex(rdm) << " ; AC <- MEM[" << converteHex(rdm) << "]" << endl;
                rem = rdm;
                rdm = memoria[rem];
                acumulador = rdm;
                count++;
                break;
            case 0x20: // STR
                programcounter += 2;
                rdm = memoria[rem + 1];

                cout << "STR " << converteHex(rdm) << " ; MEM[" << converteHex(rdm) << "] <- AC" << endl;
                rem = rdm;
                rdm = acumulador; // memoria recebe o valor do acumulador
                memoria[rem] = rdm;
                count++;
                break;
            case 0x30: // ADD
                programcounter += 2;
                rdm = memoria[rem + 1];

                cout << "ADD " << converteHex(rdm) << " ; AC <- AC + MEM[" << converteHex(rdm) << "]" << endl;
                rem = rdm;
                rdm = memoria[rem];
                acumulador += rdm;
                count++;
                break;
            case 0x40: // SUB
                programcounter += 2;
                rdm = memoria[rem + 1];

                cout << "SUB " << converteHex(rdm) << " ; AC <- AC - MEM[" << converteHex(rdm) << "]" << endl;
                rem = rdm;
                rdm = memoria[rem];
                acumulador -= rdm;
                count++;
                break;
            case 0x50: // MUL
                programcounter += 2;
                rdm = memoria[rem + 1];

                cout << "MUL " << converteHex(rdm) << " ; AC <- AC * MEM[" << converteHex(rdm) << "]" << endl;
                rem = rdm;
                rdm = memoria[rem];
                acumulador *= rdm;
                count++;
                break;
            case 0x60: // DIV
                programcounter += 2;
                rdm = memoria[rem + 1];

                cout << "DIV " << converteHex(rdm) << " ; AC <- AC / MEM[" << converteHex(rdm) << "]" << endl;
                rem = rdm;
                rdm = memoria[rem];
                acumulador /= rdm;
                count++;
                break;
            case 0x70: // NOT
                programcounter++;

                cout << "NOT ; AC <- !AC" << endl;
                rem = rdm;
                rdm = memoria[rem];
                acumulador = ~acumulador;
                count++;
            break;
            case 0x80: // AND
                programcounter +=2;
                rdm = memoria[rem + 1];
                cout << "AND ; AC <- AC & MEM[" << converteHex(rdm) << "]" << endl;
                rem = rdm;
                rdm = memoria[rem];
                acumulador = acumulador & rdm;
                count++;
            break;
            case 0x90: // OR
                programcounter += 2;
                rdm = memoria[rem + 1];
                cout << "OR ; AC <- AC | MEM[" << converteHex(rdm) << "]" << endl;
                rem = rdm;
                rdm = memoria[rem];
                acumulador = acumulador | rdm;
                count++;
            break;
            case 0xA0: // XOR
                programcounter += 2;
                rdm = memoria[rem + 1];
                cout << "AND ; AC <- AC ^ MEM[" << converteHex(rdm) << "]" << endl;
                rem = rdm;
                rdm = memoria[rem];
                acumulador = acumulador ^ rdm;
                count++;
            break;
            case 0xB0: //JMP
                programcounter += 2;
                rdm = memoria[rem + 1];
                cout << "JMP ; PC <- " << converteHex(rdm) << endl;
                programcounter = rdm;
                count++;
            break;
            case 0xC0: //JEQ
                if (acumulador == 0) {
                    programcounter += 2;
                    rdm = memoria[rem + 1];

                    cout << "JEQ ; PC <- " << converteHex(rdm) << endl;
                    programcounter = rdm;
                    count++;
                }
            break;
            case 0xD0: //JG
                if (acumulador > 0) {
                    programcounter += 2;
                    rdm = memoria[rem + 1];

                    cout << "JG ; PC <- " << converteHex(rdm) << endl;
                    programcounter = rdm;
                    count++;
                }
            break;
            case 0xE0: //JL
                if (acumulador < 0) {
                    programcounter += 2;
                    rdm = memoria[rem + 1];

                    cout << "JL ; PC <- " << converteHex(rdm) << endl;
                    programcounter = rdm;
                    count++;
                }
            break;
            case 0xF0: // HLT
                    programcounter++;

                    cout << "HLT" << endl;
                    count++;
            break;
        }
        if (instrucao == 0xF0) break; // se instrução for HTL termina a execuçao do laço
    } while (true); //Lê até encontrar o final do arquivo

    cout << endl << count << " instructions executed" << endl << endl;

    cout << "Registers:" << endl;
    cout << "AC " << setfill('0') << setw(2) << acumulador << endl;
    cout << "PC " << setfill('0') << setw(2) << programcounter << endl;
    cout << endl << "Memory:" << endl;

    for (int i = 128; i < indice + 1; i++) {
        if (memoria[i] != comp[i])
            cout << converteHex(i) << " " << setfill('0') << setw(2) << memoria[i] << endl;
    }

    return 0;
}
