namespace GOTHIC_ENGINE {
	ItemMap* iMap;

	//
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//****************************     SetLevel_Union     *****************************
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//
	HOOK Ivk_oCDocumentManager_SetLevel AS( &oCDocumentManager::SetLevel, &oCDocumentManager::SetLevel_Union );
	void oCDocumentManager::SetLevel_Union( int nDocID, zSTRING const& strLevel ) {
		THISCALL( Ivk_oCDocumentManager_SetLevel )( nDocID, strLevel );
		//cmd << "" << endl;

		iMap->nDocID = nDocID;
		iMap->strLevel = strLevel;
		iMap->strLevel.Upper();


		oCWorld* pGameWorld = dynamic_cast<oCWorld*> ( ogame->GetWorld() );
		// если имя файла не равно текущему миру, очищаем переменные
		if ( !( pGameWorld && iMap->strLevel == pGameWorld->GetWorldFilename() ) ) {
			iMap->nDocID = -1;
			iMap->strLevel = "";
		}
	}


	//
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//****************************       Show_Union       *****************************
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//
	HOOK Ivk_oCDocumentManager_Show AS( &oCDocumentManager::Show, &oCDocumentManager::Show_Union );
	void oCDocumentManager::Show_Union( int nDocID ) {
		THISCALL( Ivk_oCDocumentManager_Show )( nDocID );
		// включаем отображение наших дополнений
		if ( iMap->nDocID == nDocID ) {
			iMap->onScreen = TRUE;
		}
	}


	//
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//****************************       Draw_Union       *****************************
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//
	HOOK Ivk_zCViewDraw_Draw AS( &zCViewDraw::Draw, &zCViewDraw::Draw_Union );
	void zCViewDraw::Draw_Union() {

		THISCALL( Ivk_zCViewDraw_Draw )( );

		// ограничиваем вызов, т.к. zCViewDraw::Draw происходит не один раз за тик
		if ( iMap->onScreen && !iMap->isDraw ) {
			iMap->Draw();
			iMap->isDraw = TRUE;
		}
	}


	//
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//****************************   HandleEvent_Union    *****************************
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------
	//
	HOOK Ivk_oCDocumentManager_HandleEvent AS( &oCDocumentManager::HandleEvent, &oCDocumentManager::HandleEvent_Union );
	int oCDocumentManager::HandleEvent_Union( int nKey ) {

		if ( zinput->IsBinded( GAME_END, nKey )
			|| zinput->IsBinded( GAME_SCREEN_MAP, nKey )
			|| zinput->IsBinded( GAME_INVENTORY, nKey )
			|| ( nKey == KEY_RETURN )
			|| ( nKey == MOUSE_BUTTONRIGHT ) ) {
			this->DlgDocumentMain->RemoveAllChildren();

			this->ListDocuments->DeleteList();

			oCNpc* pPlayer = ogame->GetSelfPlayerVob();
			if ( pPlayer )
				pPlayer->SetMovLock( FALSE );

			this->SetEnableHandleEvent( FALSE );

			iMap->Clear();
		}

		// включение/отключение отображения
		if ( iMap->nDocID != -1 && zinput->IsBinded( GAME_WEAPON, nKey ) ) {
			iMap->onScreen = !iMap->onScreen;
		}

		if ( iMap->onScreen ) {
			if ( zinput->IsBinded( GAME_STRAFELEFT, nKey ) ) {
				if ( iMap->value > 0 ) {
					if ( zinput->KeyPressed( KEY_LSHIFT ) ) {
						iMap->value -= 10;
					} else {
						iMap->value--;
					}

					if ( iMap->value < 0 ) {
						iMap->value = 0;
					}
					zoptions->WriteInt( "ItemMap", "minValue", iMap->value, 30 );
					iMap->UpdateItems();
				}
			}

			if ( zinput->IsBinded( GAME_STRAFERIGHT, nKey ) ) {
				if ( zinput->KeyPressed( KEY_LSHIFT ) ) {
					iMap->value += 10;
				} else {
					iMap->value++;
				}
				zoptions->WriteInt( "ItemMap", "minValue", iMap->value, 30 );
				iMap->UpdateItems();
			}

			if ( zinput->IsBinded( GAME_UP, nKey ) ) {
				if ( iMap->category > 0 ) {
					iMap->category--;
					zoptions->WriteInt( "ItemMap", "category", iMap->category, 0 );
					iMap->UpdateItems();
				}
			}

			if ( zinput->IsBinded( GAME_DOWN, nKey ) ) {
				if ( iMap->category < ItemMap::ItemCat::CATEGORYMAX - 1 ) {
					iMap->category++;
					zoptions->WriteInt( "ItemMap", "category", iMap->category, 0 );
					iMap->UpdateItems();
				}
			}
		}

		return TRUE;
	}
}