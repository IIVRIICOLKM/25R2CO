package org.sc05.scwebappmall.service;

import lombok.Getter;
import org.sc05.scwebappmall.entity.Product;
import org.sc05.scwebappmall.entity.ProductCartItem;
import org.sc05.scwebappmall.repository.ProductCartItemRepository;
import org.sc05.scwebappmall.repository.ProductRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;

@Service
@Getter
public class ProductCartService {

    @Autowired
    private ProductCartItemRepository productCartItemRepository;
    private ProductRepository productRepository;

    /* 메모리 상에서 장바구니 관리 */
    private List<ProductCartItem> cart = new ArrayList<>();

    /* 장바구니에 상품 추가 */
    public void addProductToCart(Long productId, int quantity)
    {
        Product product = productRepository.findById(productId)
                .orElseThrow(() -> new RuntimeException("일치하는 상품을 찾을 수 없습니다."));
        ProductCartItem productCartItem = new ProductCartItem(product, quantity);
        cart.add(productCartItem);
        productCartItemRepository.save(productCartItem);
    }
    /* 장바구니에서 상품 제거 */
    public void removeProductFromCart(Long cartItemId)
    {
        ProductCartItem productCartItem = cart.stream().filter(item -> item.getId().equals(cartItemId)).findFirst()
                .orElseThrow(()-> new RuntimeException("장바구니에 " + cartItemId + "번 상품이 없습니다."));
        cart.remove(productCartItem);
        productCartItemRepository.delete(productCartItem);
    }
    /* 장바구니 품목의 총액 계산 */
    public int getTotalPrice()
    {
        return cart.stream().mapToInt(ProductCartItem::getTotalPrice).sum();
    }
}

/* 상품 저장소 비즈니스 로직 */