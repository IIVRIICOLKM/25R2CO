CREATE TABLE IF NOT EXISTS product (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    content VARCHAR(255) NOT NULL,
    price int,
    stock int
);

INSERT INTO product (name, content, price, stock) VALUES ('name 1', '신발 1', 1000, 1);
INSERT INTO product (name, content, price, stock) VALUES ('name 2', '신발 2', 2000, 2);
INSERT INTO product (name, content, price, stock) VALUES ('name 3', '신발 3', 3000, 3);
#ALTER TABLE product AUTO_INCREMENT = 1; 쿼리 입력 시 자동적으로 시작 데이터 id = 1로 초기화