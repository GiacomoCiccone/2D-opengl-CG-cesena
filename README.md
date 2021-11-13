# Progetto scena 2D

## Istruzioni per la compilazione

Il progetto utilizza la libreria [Libnoise](http://libnoise.sourceforge.net/tutorials/tutorial1.html) per generare le nuvole, quindi bisogna linkarla nella fase di compilazione. Inserire innanzitutto il file `libnoise.dll` nella directory `debug`. Dopodiche', andare nelle proprieta' del progetto -> `C/C++` -> `Directory di inclusione aggiuntive` -> `modifica` e aggiungere il patch della cartella `Include`.

<img src=".\Images\image-20211113114800504.png" alt="image-20211113114800504" style="zoom:50%;" />

 Poi andare in `Linker` -> `Generale` -> `Directory di librerie aggiuntive` -> `modifica` e aggiungere il path della cartella `Lib`.

<img src=".\Images\image-20211113114610481.png" alt="image-20211113114610481" style="zoom: 50%;" />

Infine andare in `Linker` -> `Input` -> `Dipendenze aggiuntive` -> `Modifica` e aggiungere la stringa `libnoise.dll`.

<img src=".\Images\image-20211113114841385.png" alt="image-20211113114841385" style="zoom:50%;" />

A questo punto, assumendo che vi siano i package `nupengl.core` e `glm` installati il progetto dovrebbe poter essere compilato.

## Istruzioni per giocare

Per muoversi verso destra premere `D` mentre per muoversi verso sinistra `A`. Per saltare premere `space`. L'obiettivo del gioco e' raccogliere 7 stelline sparse per la mappa. La mappa arriva fino ad un certo punto, oltre il quale non si puo' piu' andare.

## Scheenshots

<figure>
<img src=".\Images\image-20211113115059058.png" alt="image-20211113115059058" style="zoom:50%;" />
<p align="center">
    <i>1) Partita appena iniziata</i>
</p>
</figure>

<hr/>

<figure>
<img src=".\Images\image-20211113115147088.png" alt="image-20211113115147088" style="zoom:50%;" />
<p align="center">
    <i>2) Raccolta pallina verde</i>
</p>
</figure>

<hr/>

<figure>
<img src=".\Images\image-20211113115743535.png" alt="image-20211113115743535" style="zoom:50%;" />
<p align="center">
    <i>3) Partita finita</i>
</p>
</figure>


## Osservazioni

Per il testo e' stata utilizzata una libreria differente da *Freetype* e con molte meno funzionalita'. Ad esempio non ho trovato un modo semplice per evitare di renderizzare il bordo dei caratteri di colore nero. La ragione per cui non ho usato *Freetype* e' che la suddetta libreria funziona a 64 bit, e questo entrava in contrasto con la libreria `libnoise` che funziona a 32 bit.

## Autore

Giacomo Ciccone - email: giacomo.ciccone2@studio.unibo.it

