

namespace GOTHIC_ENGINE {

#define ToStr (zSTRING) 
#define printWin(a) ogame->game_text->Printwin(ToStr a); 
#define F(a) a * 81.919998		

class ItemMap {
public:
	struct Item {
		zCOLOR color;
		zPOS pos;
		int cat;
	};

	enum ItemCat {
		ALL,
		COMBAT,
		POTION,
		FOOD,
		ARMOR,
		MAGIC,
		RUNE,
		DOCS,
		OTHER,
		CHEST,
		NPC,
		CATEGORYMAX
	};


	int nDocID;
	zSTRING strLevel;

	int onScreen;

	int value;
	zCArray<Item> items;
	zCArray<zCOLOR> colors;
	zPOS pixelSize;
	zSTRING texture;
	zSTRING textureHelp;
	int update;
	int category;

	zCView * pView;
	zCView * pViewHelp;
	int isDraw;

	void Init();
	void Draw();
	void Loop();
	void UpdateItems();
	void AddItem( zPOS pos, int cat, zCOLOR color );
	void Clear();
	int GetCurrentFlags();
	zSTRING GetCategoryName();
	zPOS GetPos( zCVob * vob );
	zCOLOR GetColorFromHex( zSTRING hex );
	zCOLOR GetItemColor( int mainflag );
};
}