                            TEMA 1 EGC - Petre Cosmin 333CB

    Pentru aceasta tema am avut de implementat brick breaker. Pentru inceput
mi-am creat meshele necesare desenarii scenei(pereti, platforma, bila, power
si caracterul G pentru a felicita castigatorul). Am obtinut coordonate si
dimensiuni din rezolutia ferestrei, excluzand cateva viteze pe care le-am
ales cat mai corespunzator.
    
    Am coordonat miscarea platformei cu miscarea mouse-ului, iar bila, daca
nu a fost lansata, se va misca la fel. Bila este lansata initial pe OY,
urmand sa isi schimbe velocitatile la coliziuni astfel:
    - daca este wall sau brick, se reflecta perfect
    - daca este platforma, se calculeaza unghiul ce va fi folosit la calculul
velocitatilor

    In cazul in care a fost sparta o caramida, exista 50% sanse sa fie generat
un nou powerup. Efectul de scalare al stergerii caramizii se foloseste de timpul
de stergere totala(0.3s). Powerup-urile vor cadea cu o viteza constanta, rotindu-
-se cu un unghi specific. Daca platforma se intersecteaza cu powerup-ul, se obtin
noile puteri, fiind anulate cele vechi. Tipuri puteri:
    - adaugare viata(maxim 4)
    - marire platforma
    - miscorare platforma
    - miscare bila slow-motion

    Cand numarul vietilor ajunge la 0, meciul este resetat acordandu-se inca o
viata incepatorului. Daca se termina jocul se felicita profesionistul cu un
mesaj corespunzator "GG".