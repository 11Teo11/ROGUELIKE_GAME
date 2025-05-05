ROGUELIKE_GAME

Instructiuni player:
WASD -> pentru a te misca

sageti sus, jos, dreapta, stanga -> pentru a impusca cu proiectile

Pentru a juca -> dublu-click pe build_and_run.bat


Cerinte - TEMA 2

* separarea codului din clase in fisiere header si surse ✅ ( in folderul src )
	- fara using namespace std ✅

* mosteniri
	- minim o clasa de baza si 3 clase derivate din aceeasi ierarhie ✅ ( Entity -> Player, Enemy, Projectile; GameException -> AssetsLoadException, EntityCreationException)
 	- ierarhia trebuie sa fie cu baza proprie ✅ ( Entity.h ) 

* functii virtuale (pure)
	- minim o functie virtuala va fi specifica temei ✅ ( update, draw, getPosition)
	- functiile virtuale vor fi apelate prin pointeri la clasa de baza ✅ ( prin Entity* in Player.cpp si Game.cpp)
	- pointerii la clasa de baza vor fi atribute ale altei clase, nu doar pointeri/referinte in main ✅ ( in Game.h -> std::vector<Entity*>)

* constructori virtuali (clone) ✅

* clasa cu atribut de tip pointer la o clasa de baza cu derivate ✅ ( Game.h )

	- dynamic_cast ✅ ( in Player.cpp in updateProjectiles si in Game.cpp)

* exceptii
  	- ierarhie proprie derivata din std::exception ✅ ( GameException -> AssetsLoadException, EntityCreationExcpetion)
  	- minim 3 clase pentru erori specifice distincte 2/3
  	- throw in constructor ( Main.cpp ) catch in main ✅

* functii si atribute statice ✅ ( in Entity.h )

* cat mai multe const ✅

* STL ✅


Bibliografie

https://youtube.com/playlist?list=PLs6oRBoE2-Q_fX_rzraQekRoL7Kr7s5xi&si=xo4ucD_nmqxjzWZu

https://www.sfml-dev.org/


Assets

harta: https://scut.itch.io/7drl-tileset-2018

player: https://beowulf.itch.io/free-pixel-dungeon-explorer-16x16

inamici: https://opengameart.org/content/grue
