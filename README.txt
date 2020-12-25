Setup in Visual Studio
	Visual Studio öffnen
	Rechts oben "Clone a repository" clicken
	Den Anweisungen folgen.
	
	Wenn das Repository geklont ist (sollte in der Konsole stehen):
	Warten bis CMake den Cache generiert hat (dauert ein bisschen, weils erst raylib runterlädt)
	Wenn im Output unten "CMake generation finished." steht, in Visual Studio auf das CMakeLists.txt,
	was direkt im "prog-2-project-team-b"-Ordner liegt, rechtsklicken und Debug anklicken.
	
	Der Einfachheit halber kann man auf das erwähnte CMakeLists.txt rechtsklicken und "Set as Startup Item" klicken.
	Damit muss man nur noch F5/CTRL+F5 drücken um zu Debuggen/Runnen.
	
	Neue Source-Dateien gehören in src/game/[ordner]/
	Wenn ihr Source-Dateien hinzufügt, müsst ihr den CMake-Cache selbstständig neu generieren lassen.
	Dazu wieder auf das CMakeLists.txt im "prog-2-project-team-b"-Ordner rechtsklicken und "Generate CMake Cache" anklicken.

Struktur:
	Den Rahmen des Programms bildet die "Game"-Klasse (src/game/core/). Die Funktionen "initSpriteSheets",
	"initAnimations" und "initEntities" werden zum Programmstart ausgeführt (später kommen mindestens noch "initMusic" und "initSounds" dazu).
	Alle im Programmverlauf benötigten Assets (initSpriteSheets & initAnimations) und zum Programmstart benötigten Entities (initEntities)
	müssen hier initialisiert werden. "input", "update" und "draw" werden jeden Frame aufgerufen und handlen User-Input (input),
	führen Spiel-Logik aus (update) und zeichnen die Spielelemente ins Fenster (draw).
