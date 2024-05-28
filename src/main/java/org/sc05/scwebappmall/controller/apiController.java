package org.sc05.scwebappmall.controller;

import jakarta.annotation.Resource;
import org.sc05.scwebappmall.dto.ProductDTO;
import org.sc05.scwebappmall.entity.Product;
import org.sc05.scwebappmall.service.ProductService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import java.util.*;
import java.util.stream.Collectors;

@RestController
@RequestMapping("/api/products")
public class apiController {
    /*스프링 객체 주입*/
    @Autowired
    private ProductService productService;
    /* 상품 목록 조회 엔드포인트 */
    @GetMapping("/")
    public List<ProductDTO> getAllProduct()
    {
        return productService.findAll().stream().
                map(product -> new ProductDTO(product.getName(), product.getContent(), product.getPrice(), product.getStock()))
                .collect(Collectors.toList());
    }
    /* 상품 추가 엔드포인트 */
    @PostMapping("/")
    public ProductDTO addProduct(@RequestBody ProductDTO productDto)
    {
        Product product = productService.save(productDto.toEntity());
        return new ProductDTO(product.getName(), product.getContent(), product.getPrice(), product.getStock());
    }
    /* 상품 검색 엔드포인트 */
    @GetMapping("/search-product")
    public ResponseEntity<?> findByName(@RequestParam String name)
    {
        List<Product> products = productService.findByName(name);

        /* 검색 상품과 일치 상품 미존재 시 404_NOT_FOUND */
        if(products.isEmpty())
        {
            return new ResponseEntity<>("찾는 상품과 일치하는 상품이 없습니다.", HttpStatus.NOT_FOUND);
        }
        List<ProductDTO> productDtos = products.stream()
                .map(product -> new ProductDTO(product.getName(), product.getContent(), product.getPrice(), product.getStock())).collect(Collectors.toList());
        return new ResponseEntity<>(productDtos, HttpStatus.OK);
    }
    /* 상품 삭제 엔드포인트 */
    @DeleteMapping("/delete-product/{id}")
    public ResponseEntity<?> deleteById(@PathVariable Long id)
    {
        Optional<Product> product = productService.findById(id);
        if(product.isEmpty())
        {
            return new ResponseEntity<>(id + "번 상품이 이미 없습니다.", HttpStatus.NOT_FOUND);
        }
        productService.deleteById(id);
        return new ResponseEntity<>(id + "번 상품이 삭제되었습니다.", HttpStatus.OK);
    }
    /* 재고 상태 업데이트 엔드포인트 */
    @PutMapping("/update-stock/{id}")
    public ResponseEntity<?> updateStock(@PathVariable Long id, @RequestParam int stock)
    {
        try {
            Product updatedProduct = productService.updateStock(id, stock);
            return new ResponseEntity<>(new ProductDTO(updatedProduct.getName(), updatedProduct.getContent(),
                    updatedProduct.getPrice(), updatedProduct.getStock()), HttpStatus.OK);
        }
        catch(RuntimeException e)
        {
            return new ResponseEntity<>(e.getMessage(), HttpStatus.NOT_FOUND);
        }
    }
}


//1. 상품 재고 엔티티를 아예 상품 엔티티랑 합쳐서 데이터 수정할 때 한번에 수정할 수 있도록 하기?
//2. 판매 중단 상황 설정
//2.(1) 재고가 소진되었을 때
//2.(2) 팔던 상품이 생산 중단되었을 때(상품이 삭제되었을 때)
//2.(3)

/* 상품 기능 컨트롤러 */