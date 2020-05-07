DROP TABLE IF EXISTS qsi.parcours;
DROP TABLE IF EXISTS qsi.module;
DROP TABLE IF EXISTS qsi.cours;
DROP TABLE IF EXISTS qsi.parcours_module;
DROP TABLE IF EXISTS qsi.module_cours;


CREATE TABLE qsi.parcours (
	title VARCHAR(50) PRIMARY KEY NOT NULL,
	description VARCHAR(512)
);

CREATE TABLE qsi.module (
	title VARCHAR(50) PRIMARY KEY NOT NULL,
	description VARCHAR(512)
);

CREATE TABLE qsi.cours (
	title VARCHAR(50) PRIMARY KEY NOT NULL,
	description VARCHAR(512),
	video_url VARCHAR(200)
);

CREATE TABLE qsi.parcours_module (
	parcours VARCHAR(50),
	module VARCHAR(50),
	niveau INTEGER,
	FOREIGN KEY(parcours) REFERENCES parcours(title),
	FOREIGN KEY(module) REFERENCES module(title)
);

CREATE TABLE qsi.module_cours (
	module VARCHAR(50),
	cours VARCHAR(50),
	FOREIGN KEY(cours) REFERENCES cours(title),
	FOREIGN KEY(module) REFERENCES module(title)
);