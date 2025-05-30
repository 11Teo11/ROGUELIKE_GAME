ROGUELIKE_GAME

Instructiuni player:

Pentru a juca -> dublu-click pe build_and_run.bat

WASD -> pentru a te misca

sageti sus, jos, dreapta, stanga -> pentru a impusca cu proiectile



Cerinte - TEMA 2

* separarea codului din clase in fisiere header si surse ✅ ( in folderul src )
	- fara using namespace std ✅

* mosteniri
	- minim o clasa de baza si 3 clase derivate din aceeasi ierarhie ✅ ( Entity -> Player, Enemy, Projectile; GameException -> AssetsLoadException, EntityCreationException)
 	- ierarhia trebuie sa fie cu baza proprie ✅ ( Entity ) 

* functii virtuale (pure)
	- minim o functie virtuala va fi specifica temei ✅ ( update, draw, getPosition)
	- functiile virtuale vor fi apelate prin pointeri la clasa de baza ✅ ( prin Entity* in Player.cpp si Game.cpp)
	- pointerii la clasa de baza vor fi atribute ale altei clase, nu doar pointeri/referinte in main ✅ ( in Game.h -> std::vector<Entity*>)

* constructori virtuali (clone) ✅

* clasa cu atribut de tip pointer la o clasa de baza cu derivate ✅ ( Game.h )

	- dynamic_cast ✅ ( in Player.cpp in updateProjectiles si in Game.cpp)

* exceptii
  	- ierarhie proprie derivata din std::exception ✅ ( GameException -> AssetsLoadException, EntityCreationExcpetion, FileLoadException, FontLoadException )
  	- minim 3 clase pentru erori specifice distincte ✅ ( AssetsLoadException, EntityCreationException, FileLoadException, FontLoadException )
  	- throw in constructor ( Main.cpp ) catch in main ✅

* functii si atribute statice ✅ ( in Entity.h, Stats.h )

* cat mai multe const ✅

* STL ✅


Cerinte - TEMA 3

* Clasa sablon (template) ✅ ( Stats )

* Atribut de tip T sau care depinde de T ✅ ( T current, T maximum )

* Functie membru care sa depinda de T ✅ ( takeDamage, getRatio )

* Functie normala/libera template ✅ ( isCritical )

* Design patterns ✅ ( Game )


Bibliografie

https://youtube.com/playlist?list=PLs6oRBoE2-Q_fX_rzraQekRoL7Kr7s5xi&si=xo4ucD_nmqxjzWZu

https://www.sfml-dev.org/


Assets

harta: https://scut.itch.io/7drl-tileset-2018

player: https://beowulf.itch.io/free-pixel-dungeon-explorer-16x16

inamici: https://opengameart.org/content/grue


Link Github

https://github.com/11Teo11/ROGUELIKE_GAME
