DROP TABLE IF EXISTS parcours;
DROP TABLE IF EXISTS module;
DROP TABLE IF EXISTS cours;
DROP TABLE IF EXISTS parcours_module;
DROP TABLE IF EXISTS module_cours;


CREATE TABLE parcours (
	title VARCHAR(50) PRIMARY KEY NOT NULL,
	description VARCHAR(512)
);

CREATE TABLE module (
	title VARCHAR(50) PRIMARY KEY NOT NULL,
	description VARCHAR(512)
);

CREATE TABLE cours (
	title VARCHAR(50) PRIMARY KEY NOT NULL,
	description VARCHAR(512),
	video_url VARCHAR(200)
);

CREATE TABLE parcours_module (
	parcours VARCHAR(50),
	module VARCHAR(50),
	niveau INTEGER,
	FOREIGN KEY(parcours) REFERENCES parcours(title),
	FOREIGN KEY(module) REFERENCES module(title)
);

CREATE TABLE module_cours (
	module VARCHAR(50),
	cours VARCHAR(50),
	FOREIGN KEY(cours) REFERENCES cours(title),
	FOREIGN KEY(module) REFERENCES module(title)
);

INSERT INTO parcours VALUES ('MIAGE' , 'Un parcours de test pour tester que ça marche comme il faut');

INSERT INTO module VALUES ('Licence 3 MIAGE' , 'Un parcours de licence MIAGE pour tester que ça marche comme il faut');
INSERT INTO module VALUES ('Master 1 MIAGE' , 'Un parcours de Master 1 MIAGE pour tester que ça marche comme il faut');
INSERT INTO module VALUES ('Master 2 MIAGE' , 'Un parcours de Master 2 MIAGE pour tester que ça marche comme il faut');

INSERT INTO cours VALUES ('QSI' , 'Un cours de Master 2 MIAGE pour tester que ça marche comme il faut', 'https://video.fr');
INSERT INTO cours VALUES ('Fouille de données' , 'Un cours de Master 1 MIAGE pour tester que ça marche comme il faut', 'https://video.fr');
INSERT INTO cours VALUES ('POO' , 'Un cours de Licence 3 pour tester que ça marche comme il faut', 'https://video.fr');

INSERT INTO parcours_module VALUES ('MIAGE', 'Licence 3 MIAGE', 1);
INSERT INTO parcours_module VALUES ('MIAGE', 'Master 1 MIAGE', 2);
INSERT INTO parcours_module VALUES ('MIAGE', 'Master 2 MIAGE', 3);

INSERT INTO module_cours VALUES ('Licence 3 MIAGE', 'POO');
INSERT INTO module_cours VALUES ('Master 1 MIAGE', 'Fouille de données');
INSERT INTO module_cours VALUES ('Master 2 MIAGE', 'QSI');

--     "SELECT c.title, c.description, c.video_url
--   FROM cours AS c JOIN module_cours AS mc ON c.title = mc.cours
--   WHERE mc.module = '"
