package com.example.backstage.Service.WebSearchService;

import com.example.backstage.Entity.CatalogueEntity.Temporary;
import com.example.backstage.Entity.WebSearchEntity.Comment;
import lombok.extern.log4j.Log4j2;
import org.junit.Test;
import org.junit.Before; 
import org.junit.After; 
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.test.context.junit4.SpringRunner;
import org.springframework.test.context.web.WebAppConfiguration;

import java.util.Date;

/** 
* CommentService Tester. 
* 
* @author <Authors name> 
* @since <pre>6月 28, 2020</pre> 
* @version 1.0 
*/ 
@RunWith(SpringRunner.class)
@SpringBootTest
@WebAppConfiguration
@Log4j2
public class CommentServiceTest {
    @Autowired
    private CommentService service;

@Before
public void before() throws Exception { 
} 

@After
public void after() throws Exception { 
} 

/** 
* 
* Method: findAllByPage(Pageable pageable) 
* 
*/ 
@Test
public void testFindAllByPage() throws Exception { 
//TODO: Test goes here...
    Pageable pageable=new PageRequest(0,10);
    Page<Comment> list=service.findAllByPage(pageable);
    log.info(list.getContent());

} 

/** 
* 
* Method: addComment(Comment comment) 
* 
*/ 
@Test
public void testAddComment() throws Exception { 
//TODO: Test goes here...
    Comment comment=new Comment("cc",new Date(),"aa","bb",false);
    service.addComment(comment);
} 

/** 
* 
* Method: deleteComment(int id) 
* 
*/ 
@Test
public void testDeleteComment() throws Exception { 
//TODO: Test goes here...
     service.deleteComment(17);
} 


} 
