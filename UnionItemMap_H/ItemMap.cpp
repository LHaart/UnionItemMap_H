namespace GOTHIC_ENGINE {

	//
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//****************************     ItemMap::Init      *****************************
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//
	void ItemMap::Init() {
		nDocID = -1;
		pixelSize.X = zoptions->ReadInt( "ItemMap", "textureSize", 7 );
		pixelSize.Y = zoptions->ReadInt( "ItemMap", "textureSize", 7 );
		value = zoptions->ReadInt( "ItemMap", "minValue", 30 );

#if ENGINE >= Engine_G2
		texture = "ItemMap_Tex_G2.tga";		
		textureHelp = "ItemMap_Help_G2.tga";	
#else
		texture = "ItemMap_Tex_G1.tga";		
		textureHelp = "ItemMap_Help_G1.tga";	
#endif // ENGINE >= EngineG2

		colors.Insert( zCOLOR( 255, 255, 255 ) );
		colors.Insert( GetColorFromHex( zoptions->ReadString( "ItemMap", "colorCombat", "#E23D28" ) ) );
		colors.Insert( GetColorFromHex( zoptions->ReadString( "ItemMap", "colorPotion", "#00BFFF" ) ) );
		colors.Insert( GetColorFromHex( zoptions->ReadString( "ItemMap", "colorFood", "#00D358" ) ) );
		colors.Insert( GetColorFromHex( zoptions->ReadString( "ItemMap", "colorArmor", "#FF7F00" ) ) );
		colors.Insert( GetColorFromHex( zoptions->ReadString( "ItemMap", "colorMagic", "#FFFA00" ) ) );
		colors.Insert( GetColorFromHex( zoptions->ReadString( "ItemMap", "colorRune", "#FC00FC" ) ) );
		colors.Insert( GetColorFromHex( zoptions->ReadString( "ItemMap", "colorDocs", "#FCF3B5" ) ) );
		colors.Insert( GetColorFromHex( zoptions->ReadString( "ItemMap", "colorOther", "#898989" ) ) );


		pView = zNEW( zCView )( 0, 0, screen->anx( pixelSize.X ), screen->any( pixelSize.Y ) );
		pView->InsertBack( texture );

		pViewHelp = zNEW( zCView )( 0, 0, F( 10 ), F( 10 ) );
		pViewHelp->InsertBack( textureHelp );
		pViewHelp->SetPos( F( 88 ), F( 80 ) );
	}

	//
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//************************     ItemMap::GetItemColor      *************************
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//
	zCOLOR ItemMap::GetItemColor( int mainflag ) {
		if ( mainflag & ITM_CAT_MUN || mainflag & ITM_CAT_FF || mainflag & ITM_CAT_NF ) {
			return colors[ COMBAT ];
		} else if ( mainflag & ITM_CAT_POTION ) {
			return colors[ POTION ];
		} else if ( mainflag & ITM_CAT_FOOD ) {
			return colors[ FOOD ];
		} else if ( mainflag & ITM_CAT_ARMOR ) {
			return colors[ ARMOR ];
		} else if ( mainflag & ITM_CAT_MAGIC ) {
			return colors[ MAGIC ];
		} else if ( mainflag & ITM_CAT_RUNE ) {
			return colors[ RUNE ];
		} else if ( mainflag & ITM_CAT_DOCS ) {
			return colors[ DOCS ];
		} else {
			return colors[ OTHER ];
		}
	}

	//
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//**********************     ItemMap::GetCategoryName      ************************
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//
	zSTRING  ItemMap::GetCategoryName() {
		zSTRING cat;
		if ( category == ALL ) {
			cat = "ALL";
		} else if ( category == COMBAT ) {
			cat = "COMBAT";
		} else if ( category == POTION ) {
			cat = "POTION";
		} else if ( category == FOOD ) {
			cat = "FOOD";
		} else if ( category == ARMOR ) {
			cat = "ARMOR";
		} else if ( category == MAGIC ) {
			cat = "MAGIC";
		} else if ( category == RUNE ) {
			cat = "RUNE";
		} else if ( category == DOCS ) {
			cat = "DOCS";
		} else if ( category == OTHER ) {
			cat = "OTHER";
		} else if ( category == CHEST ) {
			cat = "CHEST";
		} else if ( category == NPC ) {
			cat = "NPC";
		}
		return cat;
	}

	//
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//**********************     ItemMap::GetCurrentFlags      ************************
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//
	int ItemMap::GetCurrentFlags() {

		int flags = ITM_FLAG_NFOCUS;
		if ( category == ItemCat::COMBAT || category == ItemCat::ALL ) {
			flags = flags | ITM_CAT_NF;
			flags = flags | ITM_CAT_FF;
			flags = flags | ITM_CAT_MUN;
		}
		flags = ( category == ItemCat::POTION	|| category == ItemCat::ALL ) ? flags | ITM_CAT_POTION : flags;
		flags = ( category == ItemCat::FOOD		|| category == ItemCat::ALL ) ? flags | ITM_CAT_FOOD : flags;
		flags = ( category == ItemCat::ARMOR	|| category == ItemCat::ALL ) ? flags | ITM_CAT_ARMOR : flags;
		flags = ( category == ItemCat::MAGIC	|| category == ItemCat::ALL ) ? flags | ITM_CAT_MAGIC : flags;
		flags = ( category == ItemCat::RUNE		|| category == ItemCat::ALL ) ? flags | ITM_CAT_RUNE : flags;
		flags = ( category == ItemCat::DOCS		|| category == ItemCat::ALL ) ? flags | ITM_CAT_DOCS : flags;
		flags = ( category == ItemCat::OTHER	|| category == ItemCat::ALL ) ? flags | ITM_CAT_LIGHT : flags;
		flags = ( category == ItemCat::OTHER	|| category == ItemCat::ALL ) ? flags | ITM_CAT_NONE : flags;

		return flags;
	}

	//
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//**********************     ItemMap::GetColorFromHex      ************************
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//
	zCOLOR ItemMap::GetColorFromHex( zSTRING hex ) {
		string str = A hex;
		str = str.Replace( "#", "" );
		int r, g, b;
		sscanf( str.GetVector(), "%02x%02x%02x", &r, &g, &b );

		zCOLOR color = zCOLOR( r, g, b );
		return color;
	}




	//
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//****************************     ItemMap::Loop      *****************************
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//
	void ItemMap::Loop() {
		// обновляем переменную для следующего тика и выводим текст
		if ( isDraw ) {
			isDraw = 0;

			zSTRING s1 = "Value: " + zSTRING( value );
			screen->Print( 8192 - screen->FontSize( s1 ) - 200, F( 72 ), s1 );

			s1 = "Category: " + GetCategoryName();
			screen->Print( 8192 - screen->FontSize( s1 ) - 200, F( 75 ), s1 );
		}
	}


	//
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//****************************      ItemMap::Draw     *****************************
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//
	void ItemMap::Draw() {
		if ( onScreen ) {
			// обновляемся один раз
			if ( update == 0 ) {
				UpdateItems();
				update = 1;
			}

			screen->InsertItem( pView );
			for ( int i = 0; i < items.GetNum(); i++ ) {
				Item item = items.GetSafe( i );
				pView->SetPos( screen->anx( item.pos.X ), screen->any( item.pos.Y ) );
				pView->SetColor( item.color );
				pView->Blit();

			}
			screen->RemoveItem( pView );

			screen->InsertItem( pViewHelp );
			pViewHelp->Blit();
			screen->RemoveItem( pViewHelp );
		}
	}

	//
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//****************************     ItemMap::GetPos    *****************************
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//
	zPOS ItemMap::GetPos( zCVob * vob ) {
		if ( !vob )
			return zPOS();

		zCWorld*	pWorld = player->GetHomeWorld();
		if ( !pWorld ) return zPOS();

		static oCDocumentManager& mgrDoc = oCDocumentManager::GetDocumentManager();
		oCViewDocumentMap* pViewDocMap = dynamic_cast<oCViewDocumentMap*> ( mgrDoc.GetDocumentView( nDocID ) );
		if ( !pViewDocMap ) return zPOS();

		zVEC3		ptVob = vob->GetPositionWorld();
		zTBBox3D	boxWorld = pWorld->GetBspTree()->bspRoot->bbox3D;

#if ENGINE >= Engine_G2
		
		zVEC2		vecWorldItem( ptVob[ VX ], ptVob[ VZ ] );

		zVEC2		vecWorldMin;  // left, bottom
		zVEC2		vecWorldMax;  // right, top
		if ( ( pViewDocMap->LevelCoords[ VX ] == 0.0f ) && ( pViewDocMap->LevelCoords[ VY ] == 0.0f ) &&
			( pViewDocMap->LevelCoords[ VZ ] == 0.0f ) && ( pViewDocMap->LevelCoords[ VW ] == 0.0f ) ) {
			// old style (obsolete) - get bounds from static level mesh

			vecWorldMin[ VX ] = boxWorld.mins[ VX ];  // left
			vecWorldMin[ VY ] = boxWorld.mins[ VZ ];  // bottom
			vecWorldMax[ VX ] = boxWorld.maxs[ VX ];  // right
			vecWorldMax[ VY ] = boxWorld.maxs[ VZ ];  // top
		} else {
			// previously set level coordinates
			vecWorldMin[ VX ] = pViewDocMap->LevelCoords[ VX ];  // left
			vecWorldMin[ VY ] = pViewDocMap->LevelCoords[ VW ];  // bottom
			vecWorldMax[ VX ] = pViewDocMap->LevelCoords[ VZ ];  // right
			vecWorldMax[ VY ] = pViewDocMap->LevelCoords[ VY ];  // top
		}

		//								
		//	GET 2D COORDS				
		//								
		zPOS		ptMapMin = pViewDocMap->ViewPageMap->PixelPosition;
		zPOS		ptMapMax = pViewDocMap->ViewPageMap->PixelSize;
		ptMapMax += ptMapMin;

		zVEC2		vecMapMin( (zREAL)ptMapMin.X, (zREAL)ptMapMin.Y );
		zVEC2		vecMapMax( (zREAL)ptMapMax.X, (zREAL)ptMapMax.Y );

		zVEC2		vecMapDir = vecMapMax - vecMapMin;
		zVEC2		vecWorldToMap = vecMapDir;
		zVEC2		vecWorldDir = vecWorldMax - vecWorldMin;
		vecWorldToMap[ VX ] /= vecWorldDir[ VX ];
		vecWorldToMap[ VY ] /= vecWorldDir[ VY ];

		zVEC2		vecMapVob = vecWorldItem - vecWorldMin;
		vecMapVob[ VX ] *= vecWorldToMap[ VX ];
		vecMapVob[ VY ] *= vecWorldToMap[ VY ];

		vecMapVob[ VY ] = vecMapDir[ VY ] - vecMapVob[ VY ];
		vecMapVob += vecMapMin;

		zPOS		ptVobPosition = zPOS( (int)vecMapVob[ VX ], (int)vecMapVob[ VY ] );
		//ptVobPosition.X -= pixelSize.X / 2;
		//ptVobPosition.Y -= pixelSize.X / 2;
		return ptVobPosition;
#else
		zPOS ptVobPosition;
		ptVobPosition.X = ( pViewDocMap->ViewPageMap->PixelSize.X + pViewDocMap->ViewPageMap->PixelPosition.X * 2 ) * 0.5 + pViewDocMap->ViewPageMap->PixelSize.X / ( boxWorld.maxs[ 0 ] - boxWorld.mins[ 0 ] ) * ptVob[ 0 ];
		ptVobPosition.Y = ( pViewDocMap->ViewPageMap->PixelSize.Y + pViewDocMap->ViewPageMap->PixelPosition.Y * 2 ) * 0.5 - pViewDocMap->ViewPageMap->PixelSize.Y / ( boxWorld.maxs[ 2 ] - boxWorld.mins[ 2 ] ) * ptVob[ 2 ];
		//ptVobPosition -= zPOS( pViewDocMap->PixelSize.X / 2, pViewDocMap->PixelSize.Y / 2 );
		return ptVobPosition;
#endif // ENGINE >= EngineG2
		
	}

	//
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//****************************  ItemMap::UpdateItems  *****************************
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//
	void ItemMap::UpdateItems() {
		items.DeleteList();

		oCWorld* pGameWorld = dynamic_cast<oCWorld*> ( ogame->GetWorld() );


		if ( pGameWorld ) {
			//-----------------------------------------
			//*************    CHEST    ***************
			//-----------------------------------------
			if ( category == ItemCat::CHEST ) {

				zCArray<zCVob*> arrVobs;
				ogame->GetWorld()->SearchVobListByClass( oCMobContainer::classDef, arrVobs, NULL );

				for ( int i = 0; i < arrVobs.GetNum(); i++ ) {
					if ( oCMobContainer* chest = zDYNAMIC_CAST<oCMobContainer>( arrVobs[ i ] ) ) {
						//*************   Chest has items    ***************
						if ( chest->containList.GetNextInList() ) {
							zPOS ptVobPosition = GetPos( chest );
							if ( !( ptVobPosition.X == 0 && ptVobPosition.Y == 0 ) ) {
								if ( chest->locked ) {
									//*************    LOCKPICK    ***************
									if ( chest->keyInstance.IsEmpty() ) {
										AddItem( ptVobPosition, CHEST, zCOLOR( 255, 128, 0 ) );
									}
									//*************    KEY    ***************
									else {
										AddItem( ptVobPosition, CHEST, zCOLOR( 180, 15, 15 ) );
									}
								}
								//*************   Opened and has items    ***************
								else {
									AddItem( ptVobPosition, CHEST, zCOLOR( 15, 180, 15 ) );
								}
							}
						}
					}
				}
			}

			//-----------------------------------------
			//**************    NPC    ****************
			//-----------------------------------------
			else if ( category == ItemCat::NPC ) {

				zCListSort<oCNpc>* voblist_npcs = pGameWorld->voblist_npcs;

				while ( voblist_npcs ) {
					oCNpc * pNpc = voblist_npcs->data;
					voblist_npcs = voblist_npcs->next;

					if ( pNpc
						&& !pNpc->IsDead()
						&& !pNpc->IsAPlayer() ) {

						zPOS ptVobPosition = GetPos( pNpc );
						if ( !( ptVobPosition.X == 0 && ptVobPosition.Y == 0 ) ) {
							AddItem( ptVobPosition, NPC, zCOLOR( 15, 180, 15 ) ); //zCOLOR(15, 180, 15)
						}
					}
				}

			}
			//-----------------------------------------
			//*************    Items    ***************
			//-----------------------------------------
			else {

				int flags = GetCurrentFlags();

				zCListSort<oCItem>* voblist_items = pGameWorld->voblist_items;

				while ( voblist_items ) {
					oCItem * pItem = voblist_items->data;
					voblist_items = voblist_items->next;

					if ( pItem
						&& !pItem->HasFlag( ITM_FLAG_NFOCUS )
						&& ( pItem->mainflag & ( flags ) )
						&& pItem->value >= value
						/* && pItem->GetPositionWorld().Distance(player->GetPositionWorld()) < 10000*/ ) {

						zPOS ptVobPosition = GetPos( pItem );
						if ( !( ptVobPosition.X == 0 && ptVobPosition.Y == 0 ) ) {
							AddItem( ptVobPosition, category, GetItemColor( pItem->mainflag ) );
						}
					}
				}

			}
		} //pGameWorld
	}

	//
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//****************************    ItemMap::AddItem    *****************************
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//
	void ItemMap::AddItem( zPOS pos, int cat, zCOLOR color ) {

		Item item;
		item.pos = pos;
		item.color = color;
		item.cat = cat;

		items.Insert( item );
	}

	//
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//****************************     ItemMap::Clear     *****************************
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//
	void ItemMap::Clear() {
		onScreen = FALSE;
		items.DeleteList();
		nDocID = -1;
		strLevel = "";
		update = FALSE;
	}
}