#include <ECS/System/Systems.h>
#include <fstream>
#include <sstream>
#include <assert.h>

void MapSystem::Update(float deltaTime, std::vector<std::shared_ptr<Entity>>& entities_, sf::RenderWindow& wnd_)
{

}

void MapSystem::Render(sf::RenderWindow& wnd_, std::vector<std::shared_ptr<Entity>>& entities_, float deltaTime)
{

	auto mpos = sf::Mouse::getPosition(wnd_);
	

	auto& player = entities_[0];
	auto& player_pos = mpos; // entities_[0]->get<PositionComponent>();
	auto player_pos_cell = sf::Vector2i{ (int)(mpos.x / tileSize.x), (int)(mpos.y / (tileSize.y / 2.f)) };
	auto player_pos_cell_offset = sf::Vector2i{ (int)mpos.x % (int)tileSize.x, (int)mpos.y % (int)(tileSize.y / 2.f) };

	auto player_world_cell = sf::Vector2i{ (int)(player_pos_cell.y - mapOffset.y) + (int)(player_pos_cell.x - mapOffset.x),  (int)(player_pos_cell.y - mapOffset.y) - (int)(player_pos_cell.x - mapOffset.x) };
	player_world_cell.x = std::clamp(player_world_cell.x, 0, mapSize.x);
	player_world_cell.y = std::clamp(player_world_cell.y, 0, mapSize.y);

	for (int y =  0; y < mapSize.y; y++)
	{
		for (int x = 0; x < mapSize.x; x++)
		{

			auto pos = toISO((float)x, (float)y);
			auto wndPos = wnd_.mapCoordsToPixel(pos);
			if ((float)wndPos.x + (float)tileSize.x < 0.f || (float)wndPos.x >(float)wnd_.getSize().x || (float)wndPos.y + (float)tileSize.y  < 0.f || (float)wndPos.y > (float)wnd_.getSize().y)
			{
				continue;
			}

			size_t num = mapTiles[y * mapSize.x + x];
			sf::Sprite tmp;
			tmp.setTexture(tilesetTex);
			tmp.setTextureRect(tilesetTiles[num]);
			tmp.setPosition(sf::Vector2f{ pos.x,  pos.y });
			wnd_.draw(tmp);

			
		}
	}

	sf::Sprite cellIndicator;
	cellIndicator.setTexture(tilesetTex);
	cellIndicator.setTextureRect(tilesetTiles[103]);
	cellIndicator.setPosition(toISO((float)wnd_.mapPixelToCoords(mpos).x, (float)wnd_.mapPixelToCoords(mpos).y));
	wnd_.draw(cellIndicator);


	/*for (auto& player : entities_)
	{
		if (player->hasComponent<PlayerControllerComponent>())
		{
			sf::IntRect bounds = { {0,0},{wnd_.getSize().x / tileSize.x,wnd_.getSize().y / tileSize.y}};
			if (auto& pos = player->get<PositionComponent>())
			{
				if (pos->x > (wnd_.getSize().x / 2.f))
				{
					bounds.left = ((pos->x / tileSize.x) - ((wnd_.getSize().x / 2.f) / tileSize.x));
				}
				if (pos->y > (wnd_.getSize().y / 2.f))
				{
					bounds.top = ((pos->y / tileSize.y) - ((wnd_.getSize().y / 2.f) / tileSize.y));
				}
			}

			renderedImage.setActive(true);
			renderedImage.clear(sf::Color::Black);
			for (int y = bounds.top * tileSize.y; y < bounds.top + (wnd_.getSize().y / tileSize.y); y++)
			{
				for (int x = bounds.left * tileSize.x; x < bounds.left + (wnd_.getSize().x / tileSize.x); x++)
				{
					if (y * mapSize.x + x >= mapTiles.size()) { break; }
					else
					{
						iFile >> num;
						renderedImage.draw(*tiles[num].spr());
					}
				}

			}
			for (int i = bounds.top * mapSize.x + bounds.left; i < (((wnd_.getSize().y / tileSize.y) * (wnd_.getSize().x / tileSize.x) + (wnd_.getSize().x / tileSize.x)) < ) ; i++)


		}
	}*/
}

void MapSystem::setMap(std::string mapFilename_)
{
	std::ifstream iFile;
	std::string tilesetFile = "assets/data/tileset/";

	iFile.open(mapFilename_, std::ios::in);

	std::string tmpStr;
	int tmpInt;
	iFile >> tmpStr;
	assert(tmpStr.contains("MAP_FILE"));

	iFile >> mapSize.x >> mapSize.y >> tileSize.x >> tileSize.y;

	iFile >> tmpStr;
	tilesetFile.append(tmpStr);
	mapTiles.clear();
	mapTiles.reserve(mapSize.x * mapSize.y);
	for (int y = 0; y < mapSize.y; y++)
	{
		for (int x = 0; x < mapSize.x; x++)
		{
			iFile >> tmpInt;
			mapTiles.emplace_back(tmpInt);
		}
	}
	iFile.close();

	setupTileset(tilesetFile);

}

void MapSystem::setView(sf::View& view_)
{
	gameView = &view_;
}

void MapSystem::setupTileset(std::string tilesetFilename_)
{

	std::ifstream iFile;
	std::string tilesetTexFile = "assets/textures/tilesets/";

	iFile.open(tilesetFilename_, std::ios::in);

	std::string tmpStr;
	iFile >> tmpStr;
	assert(tmpStr.contains("TILESET_FILE"));

	iFile >> tilesetSize.x >> tilesetSize.y >> tileSize.x >> tileSize.y;
	iFile >> tmpStr;
	tilesetTexFile.append(tmpStr);

	tilesetTex.loadFromFile(tilesetTexFile);
	tilesetTex.setSmooth(true);
	tilesetTiles.clear();
	tilesetTiles.reserve(tilesetSize.x * tilesetSize.y);
	for (int y = 0; y < tilesetSize.y; y++)
	{
		for (int x = 0; x < tilesetSize.x; x++)
		{
			if (y * tilesetSize.x + x > tilesetTiles.capacity()) { break; }
			tilesetTiles.emplace_back(sf::IntRect{ {x * (int)tileSize.x, y * (int)tileSize.y},{(int)tileSize.x,(int)tileSize.y} });
		}
	}

	iFile.close();
}

sf::Vector2f MapSystem::toISO(float x_, float y_)
{
	float tileDivY = 2.f;
	if (tileSize.x == tileSize.y)
		tileDivY = 4.f;
	float xISO = mapOffset.x * tileSize.x + ((x_ - y_) * (tileSize.x / 2.f));
	float yISO = mapOffset.y * tileSize.y + ((x_+ y_) * (tileSize.y / tileDivY));

	return { xISO,yISO };
}

