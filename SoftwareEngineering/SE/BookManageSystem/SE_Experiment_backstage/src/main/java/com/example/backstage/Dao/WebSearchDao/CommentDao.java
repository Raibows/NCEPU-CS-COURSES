package com.example.backstage.Dao.WebSearchDao;

import com.example.backstage.Entity.MaintainEntity.Book;
import com.example.backstage.Entity.WebSearchEntity.Comment;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.query.Param;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface CommentDao extends JpaRepository<Comment,String> {

    /**
     *
     * @param pageable
     * @return
     */
    @Query(value = "select * from comment",nativeQuery = true)
    Page<Comment> findAllByPage(Pageable pageable);

    /**
     *
     * @param id
     */
    void deleteById(int id);


}
