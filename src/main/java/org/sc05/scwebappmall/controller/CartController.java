package org.sc05.scwebappmall.controller;

import org.sc05.scwebappmall.dto.ProductCartDTO;
import org.sc05.scwebappmall.dto.ProductDTO;
import org.sc05.scwebappmall.entity.Product;
import org.sc05.scwebappmall.service.ProductCartService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("api/cart")
public class CartController {
    @Autowired
    private ProductCartService productCartService;

    /* 장바구니 조회 엔드포인트 */
    @GetMapping("/")
    public ResponseEntity<ProductCartDTO> getCart()
    {
        ProductCartDTO productCartDTO = new ProductCartDTO(productCartService.getCart(), productCartService.getTotalPrice());
        return new ResponseEntity<>(productCartDTO, HttpStatus.OK);
    }
    /* 장바구니 상품 추가 엔드포인트 */
    @PostMapping("/add")
    public ResponseEntity<?> addProductToCart(@RequestParam Long productId, @RequestParam int quantity)
    {
        try
        {
            productCartService.addProductToCart(productId, quantity);
            ProductCartDTO productCartDTO = new ProductCartDTO(productCartService.getCart(), productCartService.getTotalPrice());
            return new ResponseEntity<>(productCartDTO, HttpStatus.OK);
        }
        catch (RuntimeException e)
        {
            return new ResponseEntity<>(e.getMessage(), HttpStatus.NOT_FOUND);
        }
    }
    /* 장바구니 상품 제거 엔드포인트 */
    @DeleteMapping("/remove/{cartItemId}")
    public ResponseEntity<?> removeProductFromCart(@PathVariable Long cartItemid)
    {
        try {
            productCartService.removeProductFromCart(cartItemid);
            ProductCartDTO productCartDTO = new ProductCartDTO(productCartService.getCart(), productCartService.getTotalPrice());
            return new ResponseEntity<>(productCartDTO, HttpStatus.OK);
        }
        catch(RuntimeException e)
        {
            return new ResponseEntity<>(e.getMessage(), HttpStatus.NOT_FOUND);
        }
    }
}

/* 장바구니 기능 컨트롤러 */
