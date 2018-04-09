CREATE TABLE ft_table (id INT PRIMARY KEY AUTO_INCREMENT NOT NULL, login VARCHAR(11) DEFAULT 'toto' NOT NULL, size ENUM('staff', 'student', 'other') NOT NULL, creation_date DATE NOT NULL);
