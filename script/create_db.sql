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

INSERT INTO qsi.parcours VALUES ('MIAGE' , 'Un parcours de test pour tester que ça marche comme il faut');

INSERT INTO qsi.module VALUES ('Licence 3 MIAGE' , 'Un parcours de licence MIAGE pour tester que ça marche comme il faut');
INSERT INTO qsi.module VALUES ('Master 1 MIAGE' , 'Un parcours de Master 1 MIAGE pour tester que ça marche comme il faut');
INSERT INTO qsi.module VALUES ('Master 2 MIAGE' , 'Un parcours de Master 2 MIAGE pour tester que ça marche comme il faut');

INSERT INTO qsi.cours VALUES ('QSI' , 'Un cours de Master 2 MIAGE pour tester que ça marche comme il faut', 'https://video.fr');
INSERT INTO qsi.cours VALUES ('Fouille de données' , 'Un cours de Master 1 MIAGE pour tester que ça marche comme il faut', 'https://video.fr');
INSERT INTO qsi.cours VALUES ('POO' , 'Un cours de Licence 3 pour tester que ça marche comme il faut', 'https://video.fr');

INSERT INTO qsi.parcours_module VALUES ('MIAGE', 'Licence 3 MIAGE', 1);
INSERT INTO qsi.parcours_module VALUES ('MIAGE', 'Master 1 MIAGE', 2);
INSERT INTO qsi.parcours_module VALUES ('MIAGE', 'Master 2 MIAGE', 3);

INSERT INTO qsi.module_cours VALUES ('Licence 3 MIAGE', 'POO');
INSERT INTO qsi.module_cours VALUES ('Master 1 MIAGE', 'Fouille de données');
INSERT INTO qsi.module_cours VALUES ('Master 2 MIAGE', 'QSI');
