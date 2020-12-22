package com.example.backstage.Controller.CatalogueController;

import com.example.backstage.Dao.CatalogueDao.TemporaryDao;
import com.example.backstage.Entity.CatalogueEntity.Donation;
import com.example.backstage.Entity.CatalogueEntity.Temporary;
import com.example.backstage.Entity.MaintainEntity.Book;
import com.example.backstage.ResultVO;
import com.example.backstage.Service.CatalogueService.DonationService;
import com.example.backstage.Service.CatalogueService.TemporaryService;
import com.example.backstage.Service.MatainService.BookService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import net.minidev.json.JSONObject;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

@Controller
@RequestMapping("/catalogue")
@Api("编目模块")
@CrossOrigin
public class EntryController {
    @Autowired
    private DonationService donationService;
    @Autowired
    private BookService bookService;
    @Autowired
    private TemporaryService temporaryService;

    /**
     *
     * @param object
     * @return
     */
    @RequestMapping(value = "/queryDonation",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @ApiOperation("查询捐赠目录")
    @ApiParam(name = "page,size",value = "内容、页数、大小",required = true)
    public ResultVO queryDonation(@RequestBody JSONObject object){
        int page=Integer.valueOf(object.getAsString("page"));
        int size=Integer.valueOf(object.getAsString("size"));
        Pageable pageable=new PageRequest(page,size);
        Page<Donation> list=donationService.findAll(pageable);
        if (list.getTotalElements()==0){
            return ResultVO.SUCCESS();
        }else {
            return ResultVO.SUCCESS(list);
        }
    }

    /**
     *
     * @param book
     * @return
     */
    @RequestMapping(value = "/addBook",method = {RequestMethod.POST})
    @ResponseBody
    @ApiOperation("添加书籍")
    @ApiParam(name = "book",value = "书籍信息",required = true)
    public ResultVO addBook(@RequestBody Book book){
        String isbn=book.getIsbn();
        if (bookService.findByIsbn(isbn)!=null){
            return ResultVO.SUCCESS("此书已存在!");
        }else {
            temporaryService.deleteByIsbn(isbn);
            bookService.updateBook(book);
            return ResultVO.SUCCESS("录入成功!");
        }
    }

    /**
     *
     * @param temporary
     * @return
     */
    @RequestMapping(value = "/addTemporary",method = {RequestMethod.POST})
    @ResponseBody
    @ApiOperation("录入临时书目列表")
    @ApiParam(name = "temporary",value = "临时信息",required = true)
    public ResultVO addTemporary(@RequestBody Temporary temporary){
        String isbn=temporary.getIsbn();
        temporary.setHasEntry(false);
        if (bookService.findByIsbn(isbn)!=null){
            return ResultVO.SUCCESS("书目已存在!");
        }else if (temporaryService.findByIsbn(isbn)!=null){
            return ResultVO.SUCCESS("该书已录入临时列表!");
        }
        else {
            temporaryService.addTemporary(temporary);
            return ResultVO.SUCCESS("录入临时列表成功!");
        }
    }

    /**
     *
     * @param object
     * @return
     */
    @RequestMapping(value = "/queryTemporary",method = {RequestMethod.GET,RequestMethod.POST})
    @ResponseBody
    @ApiOperation("查询临时目录")
    @ApiParam(name = "page,size",value = "内容、页数、大小",required = true)
    public ResultVO queryTemporary(@RequestBody JSONObject object){
        String name=object.getAsString("name");
        int page=Integer.valueOf(object.getAsString("page"));
        int size=Integer.valueOf(object.getAsString("size"));
        Pageable pageable=new PageRequest(page,size);
        Page<Temporary> list=temporaryService.findAll(name,pageable);
        if (list.getTotalElements()==0){
            return ResultVO.SUCCESS();
        }else {
            return ResultVO.SUCCESS(list);
        }
    }
}
