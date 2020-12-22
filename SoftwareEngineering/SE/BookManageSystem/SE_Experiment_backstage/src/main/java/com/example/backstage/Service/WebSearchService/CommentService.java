package com.example.backstage.Service.WebSearchService;

import com.example.backstage.Dao.WebSearchDao.CommentDao;
import com.example.backstage.Entity.WebSearchEntity.Comment;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;

import javax.transaction.Transactional;
import java.util.List;

@Service
@Transactional
public class CommentService {
    @Autowired
    private CommentDao commentDao;

    /**
     *
     * @param pageable
     * @return
     */
    public Page<Comment> findAllByPage(Pageable pageable){
        return commentDao.findAllByPage(pageable);
    }

    /**
     *
     * @param comment
     */
    public void addComment(Comment comment){
        commentDao.save(comment);
    }

    /**
     *
     * @param id
     */
    public void deleteComment(int id){
        commentDao.deleteById(id);
    }

}
