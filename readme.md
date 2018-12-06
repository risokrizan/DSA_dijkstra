Zadanie 3 – Popolvár
Popolvár je jednoduchý chlapec z dediny, ktorý celé dni nerobí nič iné ako vynášanie popola zo sporáka v kuchyni a programovanie pre dobročinné účely. Dnes, ako tak surfoval po internete, sa k nemu dostala veľmi pohoršujúca správa. V neďalekej krajine uniesol drak viaceré princezné a schoval sa vysoko v horách, kde je veľmi ťažký prístup a chystá sa tam zajtra o polnoci všetky princezné zjesť.
Samozrejme, že sa tomu nemôžete len tak nečinne prizerať. Vďaka moderným technológiám máte k dispozícii aj mapu, ktorú rýchlo zverejnil kráľ – otec unesených nešťastníc. Vašou úlohou je teda prirodzene čo najskôr najprv zneškodniť draka a potom zachrániť všetky unesené princezné. Predpokladajte, že drak uniesol najviac 5 princezien.
Mapa predstavuje dvojrozmernú mriežku políčok:
 
C
 
Lesný chodník
 
H
Hustý lesný porast, cez ktorý idete dva-krát pomalšie ako po lesnom chodníku
N
 
Nepriechodná prekážka (napr. príliš strmá skala)
D
Drak
 
P
Princezná
0-9
 
Teleport, ktorým sa môžete preniesť
 
G
Generátor, ktorým zapnete (energiu pre) teleporty
 Vašou úlohou je implementovať nasledovnú funkciu:
int *zachran_princezne(char **mapa, int n, int m, int t, int *dlzka_cesty);
Táto funkcia má nájsť cestu, ktorou postupovať, aby Popolvár čo najskôr zachránil všetky unesené princezné a zneškodnil draka. Mapa je vysoká n políčok a široká m políčok (1 ≤ n,m ≤ 100). Parameter t (0 ≤ t ≤ 106) určuje, kedy od začiatku vášho hľadania sa drak zobudí a zje prvú princeznú. Keďže drak lieta veľmi rýchlo, spoľahnite sa, že ak sa vám ho nepodarí zneškodniť dovtedy ako sa zobudí, princezné už nezachránite. Prechod cez lesný chodník trvá jednu jednotku času a drak sa zobudí v t-tej jednotke času, kedy už bude neskoro.
A nezabudnite, že najprv musíte zneškodniť draka, až potom môžete zachraňovať princezné (hoci by ste aj prechádzali predtým cez políčko kde je princezná). Veď ako by to bolo, keby ste bojovali s drakom pri zástupe princezien ako diváčkami...
Teleporty začnú fungovať až potom ako zapnete generátor energie pre teleporty. Každý teleport má identifikátor (jednu cifru: od 0 po 9) a nejakým teleportom sa môžete preniesť na ľubovoľné iné políčko s rovnakým identifikátorom teleportu. Keď teda nastúpite na teleport 0, tak sa môžete preniesť na akýkoľvek iné políčko s teleportom s identifikátorom 0. Prenos je okamžitý (trvá nula časových jednotiek).
Nájdenú cestu vráťte ako postupnosť súradníc (dvojíc celých čísel x,y, kde 0 ≤ x < n a 0 ≤ y < m) všetkých navštívených políčok. Na začiatku sa vždy nachádzate na políčku so súradnicami 0,0 a na poslednom navštívenom políčku musí byť jedna z unesených princezien. Ak existuje viacero rovnako dlho trvajúcich ciest, môžete vrátiť ľubovoľnú z nich. Výstupný argument dlzka_cesty nastavte na počet súradníc, ktoré ste vrátili ako návratovú hodnotu.
Implementujte vyššie uvedenú funkcionalitu čo možno najefektívnejšie. Príklad použitia vašej funkcie:
Zadanie sa vypracúva v dvoch častiach: program a dokumentácia
Odovzdávate program a dokumentáciu. Program je napísaný v programovacom jazyku C, zachováva určité konvencie písania prehľadných programov (pri odovzdávaní povedzte cvičiacemu, aké konvencie ste pri písaní kódu dodržiavali). Snažte sa, aby to bolo na prvý pohľad pochopiteľné.
Termín odovzdania prvej verzie riešenia do testovača: 1.12.2018 23:59
Verziu po dopracovaní pripomienok je potrebné druhý raz odovzdať do 8.12.2018 23:59
Textová dokumentácia obsahuje hlavičku (kto, aké zadanie odovzdáva), stručný opis použitého algoritmu, s názornými nákresmi/obrázkami, a krátkymi ukážkami zdrojového kódu, vyberajte len kód na ktorý chcete extra upozorniť. Pri opise sa snažte dbať osobitý dôraz na zdôvodnenie správnosti vášho riešenia – teda, dôvody prečo je dobré/správne. Nakoniec musí technická dokumentácia obsahovať odhad výpočtovej (časovej) a priestorovej (pamäťovej) zložitosti vášho algoritmu. Celkovo musí byť cvičiacemu jasné, že viete čo ste spravili, že viete odôvodniť, že to je správne riešenie,
a vedieť aké je to efektívne.
Dôležité poznámky: Okrem cestovania teleportom sa Popolvár presúva len v štyroch smeroch (hore, dole, doľava, doprava). Ak nie je zadané inak, prechod cez políčko trvá štandardne jednu jednotku času. Teda cez políčka s drakom, princeznou, teleportom a generátorom trvá prechod tiež jednu jednotku času. Generátor je na mape najviac jeden. Do výsledného času sa započítavajú všetky políčka, cez ktoré Popolvár prejde. Ak teda začne na políčku (0,0), prejde cez políčko (1,0) a skončí na políčku (1,1), pričom všetky tri políčka obsahujú lesný chodník, tak Popolvárovi to trvá 3 jednotky času. Zneškodnenie draka, nástup do teleportu, prenos teleportom a zapnutie generátora je okamžitá akcia, ktorých trvanie je zanedbateľné vzhľadom na čas trvania prechodu cez políčko, ich zarátavame s nulovou dĺžkou trvania. Keďže Popolvár má celú radu ďalších princezien, ktoré musí ešte zachrániť v iných častiach sveta (na vstupe je viacero kráľovstiev, v ktorých chce zachrániť princezné), musíte čo najskôr zachrániť princezné (celkovo vrátane zneškodnenia draka), aby ste mohli čím skôr prejsť do ďalšieho kráľovstva. Na zadanej mape je vyznačených najviac 5 princezien.
Ako budeme vaše riešenie hodnotiť?
Môžete získať 10 bodov, minimálna požiadavka 4 body.
7 bodov je za program a testovanie, 3 body sú za dokumentáciu, pričom body môžu byť výrazne ovplyvnené prezentáciou cvičiacemu (napr. keď neviete reagovať na otázky vzniká podozrenie, že to nie je vaša práca, a teda je hodnotená 0 bodov). Významnou zložkou hodnotenia je efektívnosť implementovaného riešenia.
Dokumentácia musí obsahovať podrobný opis ako ste si svoje riešenie testovali. (na vlastných vstupoch, protokoly z testovača sú len ako podklad k hodnoteniu, nie ako “váš” spôsob testovania).
