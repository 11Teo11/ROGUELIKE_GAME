ROGUELIKE_GAME

Instructiuni player:
WASD -> pentru a te misca

sageti sus, jos, dreapta, stanga -> pentru a impusca cu proiectile


Cerinte - TEMA 2

* separarea codului din clase in fisiere header si surse ✅ ( in folderul src )
	- fara using namespace std ✅

* mosteniri
	- minim o clasa de baza si 3 clase derivate din aceeasi ierarhie ✅ ( Entity -> Player, Enemy, Projectile)

* functii virtuale (pure)
	- minim o functie virtuala va fi specifica temei ✅ ( update, draw, getPosition) ✅
	- functiile virtuale vor fi apelate prin pointeri la clasa de baza ✅ ( print Entity* in Player.cpp si main.cpp)
	- pointerii la clasa de baza vor fi atribute ale altei clase, nu doar pointeri/referinte in main

* constructori virtuali (clone) ✅

* dynamic_cast ✅ ( in Player.cpp in updateProjectiles si in main.cpp)

* exceptii ✅ ( GameException -> AssetsLoadException, EntityCreationExcpetion)

* functii si atribute statice ✅ ( in Entity.h)

* cat mai multe const ✅

* STL ✅


Bibliografie

https://youtube.com/playlist?list=PLs6oRBoE2-Q_fX_rzraQekRoL7Kr7s5xi&si=xo4ucD_nmqxjzWZu

https://www.sfml-dev.org/


Assets

https://scut.itch.io/7drl-tileset-2018

https://beowulf.itch.io/free-pixel-dungeon-explorer-16x16

