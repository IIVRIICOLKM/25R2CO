package org.sc05.scwebappmall;

import org.sc05.scwebappmall.entity.Product;
import org.sc05.scwebappmall.service.ProductService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

import java.math.BigDecimal;
import java.util.List;

@SpringBootApplication
public class ScWebAppMallApplication /*implements CommandLineRunner*/ {

    /*@Autowired
    private ProductService productService;*/

    public static void main(String[] args) {
        SpringApplication.run(ScWebAppMallApplication.class, args);
    }

    /*@Override
    public void run(String... args) throws Exception {
        //데이터 생성
        Product product1 = new Product();
        product1.setName("상품1");
        product1.setContent("상품1 입니다.");
        product1.setPrice(1000);

        Product product2 = new Product();
        product2.setName("상품2");
        product2.setContent("상품2 입니다.");
        product2.setPrice(2000);

        productService.save(product1);
        productService.save(product2);

        List<Product> products = productService.findAll();
        products.forEach(product ->
                {
                    System.out.println("ID: " + product.getId());
                    System.out.println("Name: " + product.getName());
                    System.out.println("Context: " + product.getContent());
                    System.out.println("Price: " + product.getPrice());
                }
        );
    }*/
}
