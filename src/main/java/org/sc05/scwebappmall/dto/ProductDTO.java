package org.sc05.scwebappmall.dto;
import lombok.*;
import org.sc05.scwebappmall.entity.Product;

@Getter
@NoArgsConstructor
@AllArgsConstructor
public class ProductDTO {
    private String name;
    private String content;
    private int price;
    private int stock;

    /* DTO를 엔티티로 변경 */
    public Product toEntity()
    {
        return new Product(name, content, price, stock);
    }
}

/* 상품 DTO */