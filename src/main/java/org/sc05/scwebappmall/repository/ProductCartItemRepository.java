package org.sc05.scwebappmall.repository;

import org.sc05.scwebappmall.entity.ProductCartItem;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface ProductCartItemRepository extends JpaRepository<ProductCartItem, Long> {}
/* 장바구니 리포지토리 */
