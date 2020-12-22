package com.example.backstage.Controller.MaintainController;

import com.example.backstage.Entity.MaintainEntity.Book;
import com.example.backstage.ResultVO;
import com.example.backstage.Service.MatainService.BookService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiImplicitParams;
import io.swagger.annotations.ApiOperation;
import net.minidev.json.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import javax.servlet.http.HttpServletRequest;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;

@Controller
@RequestMapping("/maintain")
@Api("书籍管理")
@CrossOrigin
public class BookController {
    @Autowired
    BookService bookService=new BookService();

    /**
     *
     * @return
     */
    @RequestMapping(value = "/queryAllBook",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @ApiOperation("查询书籍")
    @ApiImplicitParams({
            @ApiImplicitParam(name = "book",value = "书籍信息",paramType = "query")
    })
    public ResultVO queryAllBook(@RequestBody JSONObject object){
        int page=Integer.valueOf(object.getAsString("page"));
        String name=object.getAsString("name");
        int size=Integer.valueOf(object.getAsString("size"));
        Pageable pageable=new PageRequest(page,size);
        Page<Book> list=bookService.findAllByPage(name,pageable);
        if (list.getTotalElements()==0){
            return ResultVO.SUCCESS();
        }else{
            return ResultVO.SUCCESS(list);
        }
    }


    @RequestMapping(value = "/updateBook",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @ApiOperation("更新书籍")
    @ApiImplicitParam(name = "book",value = "书籍信息",required = true)
    public ResultVO updateBook(@RequestBody Book book){
        try {
            bookService.updateBook(book);
            return ResultVO.SUCCESS("修改成功!");
        }catch (Exception e){
            return ResultVO.FAIL("修改失败!");
        }
    }
}
