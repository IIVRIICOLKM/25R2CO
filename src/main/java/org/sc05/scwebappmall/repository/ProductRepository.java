package org.sc05.scwebappmall.repository;

import org.sc05.scwebappmall.entity.Product;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface ProductRepository extends JpaRepository<Product, Long>
{
    List<Product> findByName(String name);
}
/* 상품 리포지토리 */

