void Save()
{
	config = fopen("config.txt", "w");
	fprintf(config, "%d\n", totalPlayers);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			fprintf(config, "%d %d %d\n", normal.piece[i][j][0], normal.piece[i][j][1], normal.piece[i][j][2]);
		}
	}
	fclose(config);
}

void Load()		//Called by Load game from iMouse()
{
	config = fopen("config.txt", "r");
	fscanf(config, "%d", &totalPlayers);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			fscanf(config, "%d %d %d", &normal.piece[i][j][0], &normal.piece[i][j][1], &normal.piece[i][j][2]);
		}
	}
	fclose(config);
}