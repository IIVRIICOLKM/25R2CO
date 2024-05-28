package org.sc05.scwebappmall.service;

import org.sc05.scwebappmall.entity.Product;
import org.sc05.scwebappmall.repository.ProductRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;

@Service
public class ProductService {
    @Autowired
    private ProductRepository contentProductRepository;

    public Optional<Product> findById(Long id){ return contentProductRepository.findById(id); }

    /* 전체 상품 조회 */
    public List<Product> findAll() { return contentProductRepository.findAll(); }

    /* 상품 이름으로 상품 검색(중복 포함) */
    public List<Product> findByName(String name) { return contentProductRepository.findByName(name); }

    /* 상품 추가 및 수정 */
    public Product save(Product product) { return contentProductRepository.save(product); }

    /* 상품 삭제 */
    public void deleteById(Long id)
    {
       contentProductRepository.deleteById(id);
    }

    /* 재고 업데이트 */
    public Product updateStock(Long id, int stock)
    {
        Product product = contentProductRepository.findById(id).orElseThrow(() ->
                new RuntimeException("Product not found"));
        product.updateStock(stock);
        return contentProductRepository.save(product);
    }
}
