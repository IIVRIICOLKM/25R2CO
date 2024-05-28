package org.sc05.scwebappmall.entity;

import jakarta.persistence.*;
import lombok.*;

import java.util.ArrayList;
import java.util.List;

@Getter
@Setter
@NoArgsConstructor(access = AccessLevel.PUBLIC)
@Entity
@Table(name = "product")
public class Product {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)

    /* 테이블 칼럼 생성 */
    @Column(name = "id", updatable = false)
    private Long id;
    @Column(name = "name", nullable = false)
    private String name;
    @Column(name = "content", nullable = false)
    private String content;
    @Column(name = "price", nullable = false)
    private int price;
    @Column(name = "stock", updatable = false)
    private int stock;

    //단일 상품의 정보 저장
    public Product(String name, String content, int price, int stock)
    {
        this.name = name;
        this.content = content;
        this.price = price;
        this.stock = stock;
    }

    /* 재고 수량 업데이트 */
    public void updateStock(int stock)
    {
        this.stock = stock;
    }
}
/* Product 엔티티 */
