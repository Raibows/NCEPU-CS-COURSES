package com.example.backstage.Controller.WebSearchController;

import com.alibaba.fastjson.JSONObject;
import com.example.backstage.Entity.WebSearchEntity.Comment;
import org.junit.Test;
import org.junit.Before; 
import org.junit.After; 
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.http.MediaType;
import org.springframework.test.context.junit4.SpringRunner;
import org.springframework.test.context.web.WebAppConfiguration;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;
import org.springframework.test.web.servlet.result.MockMvcResultHandlers;
import org.springframework.test.web.servlet.result.MockMvcResultMatchers;

import java.util.Date;

/** 
* CommentController Tester. 
* 
* @author 罗驰
* @since <pre>6月 24, 2020</pre>
* @version 1.0 
*/
@RunWith(SpringRunner.class)
@SpringBootTest
@AutoConfigureMockMvc
public class CommentControllerTest {
    @Autowired
    private MockMvc mvc;

@Before
public void before() throws Exception { 
} 

@After
public void after() throws Exception { 
} 

/** 
* 
* Method: addComment(@RequestBody Comment comment) 
* 
*/ 
@Test
public void testAddComment() throws Exception { 
//TODO: Test goes here...
    Comment comment=new Comment("留言单元测试",new Date(),"罗驰","软件工程",true);
    String json= JSONObject.toJSONString(comment);
    mvc.perform(MockMvcRequestBuilders.post("/search/addComment")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(json)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
}

/** 
* 
* Method: queryAll(@RequestBody JSONObject object) 
* 
*/ 
@Test
public void testQueryAll() throws Exception { 
//TODO: Test goes here...
    String str="{\"page\":0,\"size\":10}";
    mvc.perform(MockMvcRequestBuilders.post("/search/queryAllComment")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(str)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 

/** 
* 
* Method: deleteComment(@RequestBody Comment comment) 
* 
*/ 
@Test
public void testDeleteComment() throws Exception { 
//TODO: Test goes here...
    Comment comment=new Comment();
    comment.setId(15);
    String json= JSONObject.toJSONString(comment);
    mvc.perform(MockMvcRequestBuilders.post("/search/deleteComment")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(json)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 


} 
