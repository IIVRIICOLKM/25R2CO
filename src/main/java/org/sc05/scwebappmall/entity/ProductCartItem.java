package org.sc05.scwebappmall.entity;

import jakarta.persistence.*;
import lombok.AccessLevel;
import lombok.Getter;
import lombok.NoArgsConstructor;

import java.util.List;

@Entity
@Getter
@NoArgsConstructor(access = AccessLevel.PROTECTED)
public class ProductCartItem {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "product_id, nullable = false")
    private Product product;

    private int quantity;

    /* 장바구니 생성 */
    public ProductCartItem(Product product, int quantity)
    {
        this.product = product;
        this.quantity = quantity;
    }

    /* 장바구니 단일 품목의 가격 계산 */
    public int getTotalPrice()
    {
        return product.getPrice() * quantity;
    }
}
//재고보다 장바구니의 숫자가 많으면 결제가 안되는 기능 추가 예정.
