package org.sc05.scwebappmall.dto;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import org.sc05.scwebappmall.entity.ProductCartItem;

import java.util.List;
import java.util.stream.Collectors;

@Getter
@NoArgsConstructor
public class ProductCartDTO {

    private List<ProductCartItemDTO> items;
    private int totalPrice;

    public ProductCartDTO(List<ProductCartItem> items, int totalPrice)
    {
        this.items = items.stream().map(ProductCartItemDTO::new). collect(Collectors.toList());
        this.totalPrice = totalPrice;
    }
}

@Getter
@NoArgsConstructor
@AllArgsConstructor
class ProductCartItemDTO{
    private Long id;
    private String productName;
    private int quantity;
    private int totalPrice;

    /* DTO 초기화 */
    public ProductCartItemDTO(ProductCartItem productCartItem)
    {
        this.id = productCartItem.getId();
        this.productName = productCartItem.getProduct().getName();
        this.quantity = productCartItem.getQuantity();
        this.totalPrice = productCartItem.getTotalPrice();
    }
}

/* 상품 장바구니 DTO */